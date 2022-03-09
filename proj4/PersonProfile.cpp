//
//  PersonProfile.cpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#include "PersonProfile.h"
#include "RadixTree.h"

PersonProfile:: ~PersonProfile()
{

}
void PersonProfile:: AddAttValPair(const AttValPair& attval)
{
    set<string>* currVals = aVPairs.search(attval.attribute);
    set<string> newVals;
    if (currVals != nullptr)
    {
          newVals = *currVals;

    }
    newVals.insert(attval.value);
    aVPairs.insert(attval.attribute, newVals);
//    AttValPair copyAttVal = attval;
    aVPairsSet.push_back(attval);
    m_items++;
    
//    delete currVals;
}
bool PersonProfile:: GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num >= GetNumAttValPairs())
        return false;
    else
    {
        
        attval.attribute =  aVPairsSet[attribute_num].attribute;
        attval.value = aVPairsSet[attribute_num].value;
//        auto it = aVPairsSet.begin();
//        for (int i = 0 ;i<attribute_num;i++)
//            it++;
//        attval.attribute = (**it).attribute;
//        attval.value = (**it).value;
        return true;
    }
    
};
