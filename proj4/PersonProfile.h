//
//  PersonProfile.hpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include <string>
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
    PersonProfile(string name, string email);
    ~PersonProfile();
    string GetName() const;
    string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    
};


#endif /* PersonProfile_hpp */
