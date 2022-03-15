//
//  MatchMaker.cpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//

#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include  <unordered_map>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
using namespace std;
vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    vector<EmailCount> returnVec;
    vector<AttValPair> translatedAttVals;
    set<std::string> compatibleAVPairs; //want a unique list
    
    int i,j;
    AttValPair attVal;
    std::string attValStr;
    const PersonProfile* targetProfile = database->GetMemberByEmail(email);
    
    for (i = 0; i<targetProfile->GetNumAttValPairs();i++)
    {
        targetProfile->GetAttVal(i, attVal);
        attValStr = attVal.attribute + "," + attVal.value;
        
        //find corresponding compatible aVapirs for each of the target's attvals
        translatedAttVals =  translations->FindCompatibleAttValPairs(attVal);
        for (j = 0;j<translatedAttVals.size();j++)
        {
            attValStr = translatedAttVals[j].attribute + "," + translatedAttVals[j].value;
            compatibleAVPairs.insert(attValStr);
        }
    }
    
    returnVec = getCompatiblePeople(compatibleAVPairs, threshold);
    return returnVec;
}


vector<EmailCount> MatchMaker::getCompatiblePeople(const set<std::string> compatibleAVPairs, int threshold) const
{
    vector<EmailCount> comptPeople;
    unordered_map<std::string, int> emailsMap;
    vector<std::string> matchingEmails;
    EmailCount compPerson("",0);
    AttValPair searchAV;
    int i;
    for  (auto it: compatibleAVPairs)
    {
        searchAV.attribute = it.substr(0,it.find(","));
        searchAV.value = it.substr(it.find(",")+1);
        matchingEmails = database->FindMatchingMembers(searchAV);
        //add the emails to the list of compatible people
        for (i = 0;i<matchingEmails.size();i++)
        {
            // if the email has not already been added to the return map, add a new emailCount object with the email
            if (emailsMap.find(matchingEmails[i]) == emailsMap.end())
            {
                emailsMap[matchingEmails[i]] = 1;
            }
            else //if the email is already in the map update corresponding value
            {
                emailsMap.find(matchingEmails[i])->second++;
            }
        }
    }
    
    for (auto it: emailsMap) //iterate through map and get members that are above threshold
    {
        if (it.second >= threshold)
        {
            compPerson.email = it.first;
            compPerson.count = it.second;
            comptPeople.push_back(compPerson);
        }
    }
    
    sort(comptPeople.begin(), comptPeople.end(), sortPeople); //sort vectr based on number of matches and person
    
    //loop through each the traits, find people that have those trait
    return comptPeople; //remember to return empty vector if no one is above threshold
}

bool MatchMaker::sortPeople(const EmailCount &a, const EmailCount &b)
{
    if (a.count >b.count)
        return true;
    else if (a.count <  b.count )
        return false;
    return (a.email < b.email);

}
