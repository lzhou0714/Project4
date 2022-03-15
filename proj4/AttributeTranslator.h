//
//  AttributeTranslator.hpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <string>
#include <iostream>
#include <set>
#include "provided.h"
#include "RadixTree.h"

using namespace std;

class AttributeTranslator
{
public:
    AttributeTranslator() {};
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs( const AttValPair& source) const; //deal with repeats when you are getting them
private:
    RadixTree<vector<string>> translations;
    set<string> sources;
    
    
};
#endif /* AttributeTranslator_hpp */
