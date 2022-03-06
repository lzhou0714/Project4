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
using namespace std;

template <typename ValueType>

class RadixTree {
public:
    RadixTree() {};
    ~RadixTree();
    void insert(std::string key, const ValueType& value)
    {
        tester[key] = value;
        
    };
    ValueType* search(std::string key) const
    {
        auto it = tester;
        it = tester.find(key);
        if (it == tester.end())
            return nullptr;
        else
            return it->second;
    };
private:
//    struct Node
//    {
//        string key;
//        ValuType value;
//        bool endOfString;
//        Node* edges[127];
//    };
//
//    Node* root;
    map<string, ValueType> tester;
    
    
};
#endif /* RadixTree_h */
