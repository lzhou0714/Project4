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
#include <string>
#include <set>
#include <iostream>
using namespace std;


/*
 must add/retrieve attribute value pairs in better than O(N) times
 must use RadixTree
 must no use STL map of anykind
 must add no pubic member functions or variables
 */

class PersonProfile
{
public:
    PersonProfile(string name, string email): m_name(name),m_email(email), m_items(0){};
//    ~PersonProfile();
    string GetName() const {return m_name;};
    string GetEmail() const {return m_email;};
    int GetNumAttValPairs() const {return m_items;};

    bool GetAttVal(int attribute_num, AttValPair& attval) const;
    void AddAttValPair(const AttValPair& attval);
private:
    string m_name;
    string m_email;
    int m_items;
    
    RadixTree<string> aVPairs;
    
};


#endif /* PersonProfile_hpp */
