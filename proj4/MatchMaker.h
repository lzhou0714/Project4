//
//  MatchMaker.hpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include <iostream>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include <vector>
using namespace std;
class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {};
//    ~MatchMaker();
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
private:
    MemberDatabase database;
    
};

#endif /* MatchMaker_hpp */
