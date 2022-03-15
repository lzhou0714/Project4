//
//  PersonProfile.hpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include "RadixTree.h"
#include <vector>
#include <string>
#include <set>
#include <iostream>

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email): m_name(name),m_email(email), m_items(0){};
    std::string GetName() const {return m_name;};
    std::string GetEmail() const {return m_email;};
    int GetNumAttValPairs() const {return m_items;};

    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    void AddAttValPair(const AttValPair& attval);
private:
    std::string m_name;
    std::string m_email;
    int m_items;
    
    RadixTree<std::set<std::string>> aVPairs;
    std::vector<AttValPair> aVPairsSet;
    
};


#endif /* PersonProfile_hpp */
