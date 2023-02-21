#include<iostream>
#include<vector>
#include<queue>
using namespace std;vector<bool>v;queue<int>q;
void p(int n){if(!v[n]){v[n]=true;q.push(n);}}
int b(int&f,int&t){int i,n,c=-1;v.resize(max(f,t)+2);q.push(f);while(++c,(i=q.size())){while(i--){n=q.front();q.pop();if(n==t)return c;if(n>=1)p(n-1);if(n<=t)p(n+1);if(n*2<=t+1)p(n*2);}}return c;}
int main(){int f,t;cin>>f>>t;cout<<b(f,t);}