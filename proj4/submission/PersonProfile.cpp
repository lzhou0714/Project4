//
//  PersonProfile.cpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#include "PersonProfile.h"
#include "RadixTree.h"
#include <vector>
#include <set>
using namespace std;
void PersonProfile:: AddAttValPair(const AttValPair& attval)
{
    set<string>* currVals = aVPairs.search(attval.attribute);
    set<string> newVals;
    if (currVals != nullptr) //if profile already has an AV pair with attval's attribute
    {
          newVals = *currVals;
        if (newVals.find(attval.value) !=newVals.end()) //is attval's value is already mapped to attvals' attribute, do nothing
            return;
    }
    newVals.insert(attval.value);
    aVPairs.insert(attval.attribute, newVals);
    aVPairsSet.push_back(attval);
    m_items++;
    
}
bool PersonProfile:: GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num >= GetNumAttValPairs())
        return false;
    else
    {
        attval.attribute =  aVPairsSet[attribute_num].attribute;
        attval.value = aVPairsSet[attribute_num].value;
        return true;
    }
    
};
