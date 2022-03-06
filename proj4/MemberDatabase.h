//
//  MemberDatabase.hpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <string>
#include <iostream>
#include <vector>
#include "provided.h"
#include "PersonProfile.h"
using namespace std;

class MemberDatabase
{
public:
    MemberDatabase() {};
//    ~MemberDatabase();
    bool LoadDatabase(string filename) {return false;};
//    vector<string> FindMatchingMembers(const AttValPair& input) const;
//    const PersonProfile* GetMemberByEmail(string email)const;
private:
    
    
    
};


#endif /* MemberDatabase_hpp */
