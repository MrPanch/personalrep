//prod. yaishenka
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std ;

#define nptr nullptr

struct Node {
    int key;
    int pr;
    Node* L=nptr;
    Node* R=nptr;
    Node () {
        L=R=nptr;
    }
    Node (int k, int p) {
        key=k;
        pr=p;
    }
    Node (int x) {
        key=x;
    }
    void insert (int k, int p);
    int l_pr () {
        return (L == nptr ? numeric_limits<int>::lowest() : L->pr);
    }
    int r_pr () {
        return (R == nptr ? numeric_limits<int>::lowest() : R->pr);
    }
    void insert_keys(int x);
    
};

Node* Merge (Node* l, Node* r) {
    if (l==nptr || r==nptr) {
        return (l==nptr? r : l);
    }
    if (l->pr < r->pr ) {
        r->L = Merge (l,r->L);
        return r;
    } else {
        r->R = Merge(l, r->L);
        return r;
    }
}

typedef pair <Node*,Node*> pNN;


pNN Split (Node*t, int x) {
    if (t == nullptr)
    {
        return {nptr, nptr};
    } else if (x > t->key)
    {
        pNN tmp=Split(t->R,x);
        t->R=tmp.first;
        return {t,tmp.second};
    } else
    {
        pNN tmp=Split(t->L,x);
        t->L=tmp.second;
        return {tmp.first,t};
        
    }
}


void Node::insert(int k, int p)
{
    if (pr > p)
    {
        if (k<key)
        {
            if (L==nptr)
            {
                Node* tmp = new Node (k,p);
                L=tmp;
            } else
            {
                L->insert(k, p);
            }
        } else
        {
            if (R==nptr)
            {
                Node* tmp = new Node (k,p);
                R=tmp;
            } else
            {
                R->insert(k, p);
            }
        }
    } else
    {
        Node* tmp = new Node (key,pr);
        tmp->L=L;
        tmp->R=R;
        pNN tmp2 = Split(tmp, k);
        L=tmp2.first;
        R=tmp2.second;
        key=k;
        pr=p;
        return;
    }
}

void write(Node* t)
{
    if (t == nptr)
        cout << "nptr\n";
    else
        cout << t->key << ' ' << t->pr << '\n';
}





void Node::insert_keys(int x)
{
    if (L != nptr && x < key)
        L->insert_keys(x);
    else if (L == nptr && x < key)
    {
        L = new Node(x);
    }
    else if (R != nptr && x >= key)
        R->insert_keys(x);
    else if (R == nptr && x >= key)
    {
        R = new Node(x);
    }
}

int find_depth(Node* t)
{
    //cout<<t->key<<" "<<t->pr<<endl;
    int res1(0), res2(0);
    if (t->L != nptr)
        res1 = find_depth(t->L) + 1;
    if (t->R != nptr)
        res2 = find_depth(t->R) + 1;
    return max(res1, res2);
}

int main()
{
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    Node* root = new Node(a, b);
    Node* naive = new Node(a);
    --n;
    while (n--)
    {
        cin >> a >> b;
        root->insert(a, b);
        naive->insert_keys(a);
    }
    a = find_depth(naive);
    b = find_depth(root);
    cout << find_depth(naive) - find_depth(root) << endl;
    return 0;
}









