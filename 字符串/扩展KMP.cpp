#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define mt(a) memset(a,0,sizeof(a))
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll extend[1000001];
ll Next[1000001];
ll min(ll x,ll y)
{
    if(x>y) return y;
    return x;
}
void getNext(string t)
{
    mt(Next);
    ll len=t.length();
    Next[0]=len;
    ll a,p;
    a=1;
    while( a<len && t[a]==t[a-1]) a++; // 求出长度为1的时候 解为多少 
    Next[1]=a-1;
    a=1;
    for(ll i=2;i<len;i++) // 后续的按照算法来就好
    {
        p=a+Next[a]-1;
        if((i-1)+Next[i-a] < p ) Next[i]=Next[i-a];// 第一种情况 没有超过等于的部分
        else // 超过的话就不好直接用next的定义 需要后续的遍历
        {
            ll j = (p - i + 1) > 0 ? (p - i + 1) : 0;
            while(i + j < len && t[i+j] == t[j]) j++;
            Next[i]=j;
            a=i;
        }
    }
}
void exkmp(string s,string t) // s->extend  t->next
{
    getNext(t);
    ll a,p;//
    ll slen=s.length();
    ll tlen=t.length();
    a=p=0;
    ll len=min(s.length(),t.length());
    while(p<len && t[p]==s[p]) p++; // after
    extend[0]=p;
    for(ll i=1;i<slen;i++)
    {
        p=a+extend[a]-1; // update
        if( (i-1)+Next[i-a] < p) extend[i]=Next[i-a];
        else
        {
            ll j = (p - i + 1) > 0 ? (p - i + 1) : 0;
            while( j < tlen && i+j < slen && s[i + j] == t[j]) j++;
            extend[i]=j;
            a=i;
        }
    }
}
// 核心 一个起始位置a  一个最远匹配位置p 然后Next 和 extend数组
int main()
{
    string s,t;// s->exkmp t->Next
    int Case;
    scanf("%d",&Case);
    while(Case--)
    {
        cin>>s>>t;
        exkmp(s,t);
       
    }
    return 0;
}