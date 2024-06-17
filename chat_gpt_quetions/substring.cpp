#include<bits/stdc++.h>

using namespace std;


bool containsAllChars(string str, string pattern){
    unordered_map<char,int> mp;
    for(int i = 0;i<str.size();i++){
        mp[str[i]]++;
    }

    for(int j = 0;j<pattern.size();j++){
        if(mp[pattern[j]]==0){
            return false;
        }
    }
    

    

    return true;
}

string substr(string str,string pattern){
    int len_str = str.length();
    string ans = "";
    int min = INT_MAX;

    for(int i = 0;i<len_str;i++){
        for(int j = 1;j<len_str;j++){
            string sub = str.substr(i,j-i+1);

            if(containsAllChars(sub,pattern)){
                if(sub.length()<min){
                    ans = sub;
                    min = sub.length();
                }


            }

        }
    }
    return ans;

}

int main(){
    string str = "maaanmanapple";
    string pattern = "man";


    cout<<substr(str,pattern);
}