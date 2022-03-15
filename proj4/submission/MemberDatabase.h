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
#include <set>
#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"

class MemberDatabase
{
public:
    MemberDatabase(): m_numEmails(0), m_numAttValPairs(0) {};
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email)const;
private:
    RadixTree<PersonProfile*> emailToProfile;
    RadixTree<std::vector<std::string>> attValPairsToEmail;
    
    std::vector<PersonProfile*> vectProfiles;
    std::vector<std::string> listEmails;
    std::set<std::string> listAttValPairs;
    int m_numEmails;
    int m_numAttValPairs;
    
};


#endif /* MemberDatabase_hpp */
