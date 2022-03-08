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
    int firstDiff(std::string smallerStr, int a, std::string largerStr) const ;
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
void RadixTree<ValueType>:: insert(std::string key, const ValueType& value)
{
//new///////////////////////////////////////////////////////
    
    Node* currNode = rootPtr;
    rootPtr->endOfString = false;
    int breakInd = 0;
    std::string currkey = key;
    char breakPoint = key[breakInd];
    Node* currEdge =currNode->edges[breakPoint];

    while (currkey.size()>0)
    {
        if (currEdge == nullptr) //new word
        {
            addNode(currkey, new ValueType(value), currEdge);
            currNode->edges[breakPoint] = currEdge;
            break;
        }
        else
        {
            int edgeLen = currEdge->k.size();
            int currKeyLen = currkey.size();
            breakInd = firstDiff(currEdge->k, edgeLen, currkey);
            //key shares prefix with current word at edge
            //key ends on edge, if edge has value update, if not add value and indicated end of word
            if (breakInd == currKeyLen && breakInd == edgeLen)
            {
                if (currEdge->endOfString)
                {
                    delete currEdge->v;
                }
                else
                {
                    currEdge->endOfString = true;
                }
                currEdge->v = new ValueType(value);
                break;
            }
            //existing word is the prefix of key, add remaining key to end of existing word
            if (breakInd == edgeLen && breakInd < currKeyLen)
            {
                currNode = currEdge;
                currEdge = currEdge->edges[currkey[breakInd]];
            }
            if (breakInd != edgeLen)
            {
                std::string prevValAtEdge = currEdge->k;
                Node* prefix;

                //key is the prefix of word at edge, need to split into prefix and rest of preexisting word at edge
                if (breakInd == currKeyLen)
                {
                    addNode(prevValAtEdge.substr(0, breakInd), new ValueType(value),prefix);
                }
                //key is longer than the shared prefix, needs to split into prefix and two other nodes, prefix is not a word
                else
                    addNode(prevValAtEdge.substr(0, breakInd), nullptr,prefix);
                
                currNode->edges[prefix->k[0]] = prefix;
                //add remaining of preexisting word
                currNode = prefix;
                breakPoint = prevValAtEdge[breakInd];
                currNode->edges[breakPoint] = currEdge; //link remaining of edge to prefix
                currEdge->k = prevValAtEdge.substr(breakInd); //update previous val
                
                //add remaining key
                if (breakInd<currKeyLen)
                {
                    breakPoint =currkey[breakInd];
                    currEdge = currNode->edges[breakPoint];
                }
                else break;
            }
            breakPoint =currkey[breakInd];
            currkey = currkey.substr(breakInd);
        }
    }
}

template <typename ValueType>
inline
ValueType* RadixTree<ValueType>:: search(std::string key) const
{
    Node* currNode = rootPtr->edges[key[0]];
        int currIndex = 0;
        std::string currKey = key;
        while (currKey.size()>0)
        {
            
            if (currKey.size() < currNode->k.size())
                break;
            
            else if (currKey.size() == currNode->k.size() && currNode->endOfString ==true)
                return currNode->v;
            
            else
            {
                currIndex = firstDiff(currKey, currKey.size(), currNode->k);
                currKey = currKey.substr(currIndex);

                char checkPoint = currKey[0];
                currNode = currNode->edges[checkPoint];
            }
            
        }
        
        return nullptr;
    
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
int RadixTree<ValueType>::firstDiff(std::string smallerStr, int a, std::string largerStr) const
{
    int i;
    for (i = 0;i<a;i++)
    {
        if (smallerStr[i] != largerStr[i])
            return i;
    }
    return i;
}

#endif /* RadixTree_h */
