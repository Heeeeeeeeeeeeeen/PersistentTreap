/*input

7
! ababahalamaha
? a
? b
? a
? b
? a
? h
*/


#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define llu long long unsigned
#define sc(t,x) static_cast<t>(x)
#define ar(t) vector < t >
#define pii pair < int, int >
#define pll pair < LL, LL >
#define pil pair < int, LL >
#define pli pair < LL, int >
#define mp make_pair
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define fi first
#define se second
#define init(ar,val) memset ( ar, val, sizeof ( ar ) )
#define lp(loop,start,end) for ( int loop = start; loop < end; ++loop )
#define lpd(loop,start,end) for ( int loop = start; loop > end; --loop )
#define lpi(loop,start,end) for ( int loop = start; loop <= end; ++loop )
#define lpdi(loop,start,end) for ( int loop = start; loop >= end; --loop ) 
#define qmax(a,b) (((a)>(b))?(a):(b))
#define qmin(a,b) (((a)<(b))?(a):(b))
#define qabs(a) (((a)>=0)?(a):(-(a)))
#define vi vector<int>
#define mid(l,r) ((l+r)>>1)


struct node
{
    short link;
    node *l,*r;
    ll size,key,val,add;
    node(){
        l = NULL,r=NULL,key = val = size = add = link = 0;
    }
    node(node *curr){
        if(!curr) return;
        key = curr->key;
        size = curr->size;
        val = curr->val;
        add = curr->add;
        l = curr->l,r=curr->r;
        link = 0;
    }
    node(int x){
        l = r =NULL,val = key = x,size = 1,add=link=0;
    }
    void del()
    {
        link--;
        if(link<=0){
            if(l) l->del();
            if(r) r->del();
            delete this;
        }
    }
};

typedef node* nodeptr;

int size(nodeptr x)
{
    if(!x) return 0;
    return x->size;
}

void push(node *x)
{
    if(!x) return;
    x->val+=x->add;
    if(x->l) x->l->add+=x->add;
    if(x->r) x->r->add+=x->add;
    x->add = 0;
}

void addlink(nodeptr root){
    if(!root) return;
    root->link++;
}

void del(nodeptr x)
{
    if(!x) return;
    x->del();
}




ll val(node *x)
{
    if(!x) return 0;
    push(x);
    return x->val;
}

void upd(node *x)
{
    if(!x) return;
    x->size = size(x->l)+1+size(x->r);
    x->val = val(x->l)+x->key+val(x->r);
}

void split(nodeptr root,nodeptr& l,nodeptr& r,int pos)
{
    if(!root){
        l = r = NULL;
        return;
    }
    push(root);
    nodeptr curr = new node(root);
    if( size(curr->l) < pos){
        split(curr->r,curr->r,r,pos - size(curr->l)-1);
        addlink(curr->l);
        addlink(curr->r);
        l = curr;
    }else{
        split(curr->l,l,curr->l,pos);
        addlink(curr->l);
        addlink(curr->r);
        r = curr;
    }
    upd(r);
    upd(l);
}

nodeptr merge(nodeptr l,nodeptr r)
{
    nodeptr t = NULL;
    if(!l || !r){
        t = new node(l?l:r);
        addlink(t->l);
        addlink(t->r);
        return t;
    }
    int L,R,rang;
    push(l);
    push(r);
    L = size(l),R = size(r),rang = rand()%(L+R);
    if(rang>R){
        t = new node(l);
        t->r = merge(t->r,r);
        addlink(t->r);
        addlink(t->l);
        upd(t);
        return t;
    }else{
        t = new node(r);
        t->l = merge(t->l,l);
        addlink(t->r);
        addlink(t->l);
        upd(t);
        return t;
    }
}

const int n = 10;
node *t[10];

int main() {
    int a[n];
    lp(i,0,n) a[i] = i;
    t[0] = new node(a[0]);
    lp(i,1,n) t[i] = merge(t[i-1],new node(a[i]));
    nodeptr x,y;
    split(t[9],x,y,4);
    while(x->r) x=x->r;
    cout<<x->key;
}
    
