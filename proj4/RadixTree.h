//
//  RadixTree.h
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef RadixTree_h
#define RadixTree_h
using namespace std;
#include <string>
template <typename ValueType>

class RadixTree {
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
};
#endif /* RadixTree_h */
