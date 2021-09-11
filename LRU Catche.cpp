#include<bits/stdc++.h>
using namespace std;
class Node
{
public:
    string key;
    int value;
    Node(string key,int value)
    {
        this->key=key;
        this->value=value;
    }
};
class LRUcatche
{
public:
    int maxSize;
    list<Node>l;  // sought of linked list
    unordered_map<string,list<Node>::iterator>m;  // hash map for O(1) implementation of retrieval
    LRUcatche(int maxSize)
    {
        this->maxSize=maxSize>1?maxSize:1;
    }
    void insertKeyVal(string key,int val)
    {
        //2 cases
        // first: if key is already present in hash map
        if(m.count(key)!=0)
        {
            auto it=m[key];
            it->value=val;   // then just update the value of the key
        }
        //if key is not present in hash map
        else{
            //check if cache is full or not
            //if full then:
            if(l.size()==maxSize)
            {
                Node last=l.back();
                m.erase(last.key);   //remove last element of linked list from hash map
                l.pop_back();   // remove from list the last element
            }
            //if not full then: insert it in hash map and place it at head of linked list
            Node n(key,val);
            l.push_front(n);
            m[key]=l.begin();
        }
    }
    int *getValue(string key)
    {
        if(m.count(key)!=0)
        {
            auto it=m[key];
            int value=it->value;
            l.push_front(*it);
            l.erase(it);
            m[key]=l.begin();
            return &l.begin()->value;
        }
        return NULL;
    }
    string mostRecentKey()
    {
        return l.front().key;
    }
};
int main()
 {
     LRUcatche lru(3);
     lru.insertKeyVal("mango",10);
     lru.insertKeyVal("apple",20);
     lru.insertKeyVal("guava",30);
     cout<<lru.mostRecentKey()<<endl;
     lru.insertKeyVal("mango",15);
     cout<<lru.mostRecentKey()<<endl;
     int *order=lru.getValue("mango");
     if(order!=NULL)
     {
         cout<<"Order of mango "<<*order<<endl;
     }
     lru.insertKeyVal("banana",40);
     if(lru.getValue("apple")==NULL)
     {
         cout<<"Apple does not exist"<<endl;
     }
     if(lru.getValue("mango")==NULL)
     {
         cout<<"Mango does not exist"<<endl;
     }
     if(lru.getValue("guava")==NULL)
     {
         cout<<"Guava does not exist"<<endl;
     }
     return 0;
 }
