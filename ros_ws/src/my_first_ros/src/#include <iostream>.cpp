#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector <int>a;
    pair <int,int>p={a[n],n};
    for(int i=0;i<n;i++){
    cin>>a[i];
    
    }
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++){
        cout<<p.first;
      

    }
    cout<<p.second/n;
    return 0;


}