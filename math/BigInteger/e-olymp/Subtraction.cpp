#include <bits/stdc++.h>
using namespace std;

const int BASE_DIGITS = 9;
const int BASE = 1000000000;

struct BigInt {
    int sign;
    vector<int> a;

    // -------------------- Constructors --------------------
    // Default constructor.
    BigInt() : sign(1) {}

    // Constructor from long long.
    BigInt(long long v) {
        *this = v;
    }
    BigInt& operator = (long long v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v = v / BASE)
            a.push_back(v % BASE);
        return *this;
    }

    // Initialize from string.
    BigInt(const string& s) {
        read(s);
    }

    // -------------------- Input / Output --------------------
    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream& operator>>(istream &stream, BigInt &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream &stream, const BigInt &v) {
        if (v.sign == -1 && !v.isZero())
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return stream;
    }

    // -------------------- Comparison --------------------
    bool operator<(const BigInt &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = ((int) a.size()) - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator>(const BigInt &v) const {
        return v < *this;
    }
    bool operator<=(const BigInt &v) const {
        return !(v < *this);
    }
    bool operator>=(const BigInt &v) const {
        return !(*this < v);
    }
    bool operator==(const BigInt &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const BigInt &v) const {
        return *this < v || v < *this;
    }

    // Returns:
    // 0 if |x| == |y|
    // -1 if |x| < |y|
    // 1 if |x| > |y|
    friend int __compare_abs(const BigInt& x, const BigInt& y) {
        if (x.a.size() != y.a.size()) {
            return x.a.size() < y.a.size() ? -1 : 1;
        }

        for (int i = ((int) x.a.size()) - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return x.a[i] < y.a[i] ? -1 : 1;
            }
        }
        return 0;
    }

    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

    // -------------------- Unary operator - and operators +- --------------------
    BigInt operator-() const {
        BigInt res = *this;
        if (isZero()) return res;

        res.sign = -sign;
        return res;
    }

    // Note: sign ignored.
    void __internal_add(const BigInt& v) {
        if (a.size() < v.a.size()) {
            a.resize(v.a.size(), 0);
        }
        for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int) a.size()) a.push_back(0);

            a[i] += carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
    }

    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }

    // Note: sign ignored.
    void __internal_sub(const BigInt& v) {
        for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        this->trim();
    }

    BigInt operator += (const BigInt& v) {
        if (sign == v.sign) {
            __internal_add(v);
        } else {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
            }
        }
        return *this;
    }

    BigInt operator -= (const BigInt& v) {
        if (sign == v.sign) {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
                this->sign = -this->sign;
            }
        } else {
            __internal_add(v);
        }
        return *this;
    }

    // Optimize operators + and - according to
    // https://stackoverflow.com/questions/13166079/move-semantics-and-pass-by-rvalue-reference-in-overloaded-arithmetic
    template< typename L, typename R >
    typename std::enable_if<
            std::is_convertible<L, BigInt>::value &&
            std::is_convertible<R, BigInt>::value &&
            std::is_lvalue_reference<R&&>::value,
            BigInt>::type friend operator + (L&& l, R&& r) {
        BigInt result(std::forward<L>(l));
        result += r;
        return result;
    }
    template< typename L, typename R >
    typename std::enable_if<
            std::is_convertible<L, BigInt>::value &&
            std::is_convertible<R, BigInt>::value &&
            std::is_rvalue_reference<R&&>::value,
            BigInt>::type friend operator + (L&& l, R&& r) {
        BigInt result(std::move(r));
        result += l;
        return result;
    }
};

int main() {

    BigInt a, b;
    cin >> a >> b;
    a -= b;
    cout << a << endl;
}
