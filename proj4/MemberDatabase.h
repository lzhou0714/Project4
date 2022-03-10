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
#include "RadixTree.h"
using namespace std;

class MemberDatabase
{
public:
    MemberDatabase(): m_numEmails(0), m_numAttValPairs(0) {};
    ~MemberDatabase() {};
    bool LoadDatabase(string filename);
//    vector<string> FindMatchingMembers(const AttValPair& input) const;
//    const PersonProfile* GetMemberByEmail(string email)const;
private:
    RadixTree<PersonProfile*> emailToProfile;
    RadixTree<vector<string>> attValPairsToEmail;
    
    vector<string> listEmails;
    set<string> listAttValPairs;
    int m_numEmails;
    int m_numAttValPairs;
    
    
    
    
};


#endif /* MemberDatabase_hpp */
