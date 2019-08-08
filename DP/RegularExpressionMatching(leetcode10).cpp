#include<bits/stdc++.h>
#define vb vector<bool>
using namespace std;
#define siz(x) (int)x.size()
class Solution {
public:
    
    bool solve(string text, string pattern){
    //string text,pattern;
    //cin>>text>>pattern;
    int n=siz(text),m=siz(pattern);

    vector< vb > matrix(n+1,vb(m+1,false));
    matrix[0][0]=true;
        
    for(int i=0;i<m;i++){
        if(pattern[i]=='*'){
            matrix[0][i+1]=(i>=1? matrix[0][i-1]:false);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(pattern[j]==text[i] or pattern[j]=='.')
                matrix[i+1][j+1]=matrix[i][j];
            else if(pattern[j]=='*'){
                if(j>0 and matrix[i+1][j-1])
                    matrix[i+1][j+1]=true;
                else if(pattern[j-1]==text[i] or pattern[j-1]=='.'){
                    matrix[i+1][j+1]=matrix[i][j+1];
                }
            }
        }
    }
    return matrix[n][m];
    }
    
    bool isMatch(string s, string p) {
        return solve(s,p);
    }
};
