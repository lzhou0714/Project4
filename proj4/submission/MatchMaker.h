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
class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at):
    database(&mdb), translations(&at) {} 
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    std::vector<EmailCount> getCompatiblePeople(const std::set<std::string> compatibleAVPairs, int threshold) const;
    static bool sortPeople(const EmailCount& a, const EmailCount &b);
    const MemberDatabase* database;
    const AttributeTranslator* translations;
};

#endif /* MatchMaker_hpp */
