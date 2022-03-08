//
//  RadixTree.h
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <map>
#include <vector>

template <typename ValueType>

class RadixTree {
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    struct Node
    {
        Node(std::string key, ValueType* val)
        {
            k = key;
            v = val;
            endOfString = true;
            for (int i=0;i<128;i++)
            {
                edges[i] = nullptr;
            }
        }
        std::string k;
        ValueType* v;
        bool endOfString;
        Node* edges[128];
    };
    Node* rootPtr;
    void deletionHelper(Node* nodeptr);
    int firstDiff(std::string smallerStr, int a, std::string largerStr);
    void addNode(std::string key,  ValueType* value,Node*& target);
    
};

template <typename ValueType>
inline
RadixTree<ValueType>:: RadixTree()
{
    rootPtr = new Node("",nullptr);

}
template <typename ValueType>
inline
RadixTree<ValueType>:: ~RadixTree()
{
    Node* nodeptr = rootPtr;
    deletionHelper(nodeptr);
}

template <typename ValueType>
inline
void RadixTree<ValueType>::addNode(std::string key, ValueType* value, Node*& target )
{
    target = new Node(key, value);
    if (value == nullptr)
        target->endOfString = false;
}

template <typename ValueType>
inline
void RadixTree<ValueType>::deletionHelper(Node* nodeptr)
{
    if (nodeptr == nullptr)
        return;
    for (int i  = 0;i<128;i++)
    {
        if (nodeptr->edges[i] != nullptr)
        {
            deletionHelper(nodeptr->edges[i]);
        }
    }
    if (nodeptr->v!=nullptr)
    {
        delete nodeptr->v;
    }
    delete nodeptr;
    
}

template <typename ValueType>
inline
void RadixTree<ValueType>:: insert(std::string key, const ValueType& value)
{
    Node* currNode = rootPtr;
//    Node* prev = nullptr;
    rootPtr->endOfString = false;
    int currIndex = 0;
    //if search returns true return immediately
    while (currIndex<key.length())
    {
        char breakPoint = key[currIndex];
        std::string currkey = key.substr(currIndex);
        Node* currEdge =currNode->edges[breakPoint];
        if (currEdge == nullptr) //new word
        {
            addNode(key.substr(currIndex,key.size()), new ValueType(value), currEdge);
            currNode->edges[breakPoint] = currEdge;
            break;
        }
        else
        {
            int a = currEdge->k.size();
            int b = currkey.size();
            int breakInd  = firstDiff(currEdge->k,a,currkey);
            if (breakInd>=a)
            {
                if (a == b) //key ends on this node
                {
                    currEdge->endOfString = true;
                    currEdge->v = new ValueType(value);
                    break;
                }
                    
                currIndex += breakInd; //add edge to end of node
                currNode = currNode->edges[breakPoint];
                continue;
            }
            else //branches off
            {
                //prefix
                std::string prevKey = currEdge->k;
                Node* prefix; //prefix

                if (breakInd==b) //b ==prefix
                    addNode(prevKey.substr(0, breakInd), new ValueType(value),prefix);
                else
                    addNode(prevKey.substr(0, breakInd), nullptr,prefix);

                currNode->edges[breakPoint] = prefix;
                
//                prev = currNode;
                currNode = prefix;
                //add remaining of existing key
                breakPoint = prevKey[breakInd];
                currNode->edges[breakPoint] = currEdge;
                currEdge->k = prevKey.substr(breakInd, prevKey.size());
                //if the original string has no remaining substring after breaking off the prefix delete the node
                currNode->edges[breakPoint] = currEdge;
                if (breakInd<=b)
                {
                    currIndex += breakInd;
                }
            }
        }
    }
}
template <typename ValueType>
inline
int RadixTree<ValueType>::firstDiff(std::string smallerStr, int a, std::string largerStr)
{
    int i;
    for (i = 0;i<a;i++)
    {
        if (smallerStr[i] != largerStr[i])
            return i;
    }
    return i;
}

template <typename ValueType>
inline
ValueType* RadixTree<ValueType>:: search(std::string key) const
{
    ValueType* x;
    return x;
}
#endif /* RadixTree_h */
