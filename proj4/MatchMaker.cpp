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
#include <utility>

//
//MatchMaker::~MatchMaker()
//{
//    delete database;
//    delete translations;
//}


//WEIRD STUFF GOING ON WITH MEMORY ALLOCATION???////



vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
//    Translate Anisha’s attribute-value pairs into a set of three compatible attribute-value pairs:
//    a. likes,baking (both likes,cookies and likes,brownies translate to likes,baking, but we consider likes,baking only once)
//    b. likes,reviewing code
//    c. occupation,QA engineer
//    2. Identify members that match likes,baking and find Tjader, Hercumur, and Angus
//    3. Identify members that match likes,reviewing code and find Hercumur, and Andrea
//    4. Identify members that match occupation,QA engineer and find Hercumur, Angus, and
//    Andrea
//    5. So Hercumur has 3 compatible attribute-value pairs, Angus has 2 compatible pairs,
//    Andrea has 2 compatible pairs, and Tjader has 1 compatible pair
//    6. We’d then output the following member emails and counts in this order:
//    a. hercumur@gmail.com, 3
//    b. andrea@gmail.com, 2
//    c. angus@gmail.com, 2
    
    //get person;s profile
    //get person;s attval pairs
    //translate person's attval pairs (attribuye translators)
    //get the attval pairs that are compatible to the person's attval pairs
    //find the people that have those attval pairs
    int i,j;
    vector<EmailCount> returnVec;
    vector<std::string> targetAttVals;
    vector<AttValPair> translatedAttVals;
    set<std::string> compatibleAVPairs; //want a unique list
    
    AttValPair attVal;
    std::string attValStr;
    const PersonProfile* targetProfile = database->GetMemberByEmail(email);
    for (i = 0; i<targetProfile->GetNumAttValPairs();i++)
    {
        targetProfile->GetAttVal(i, attVal);
        attValStr = attVal.attribute + "," + attVal.value;
        targetAttVals.push_back(attValStr);
        
        //find corresponding compatible aVapirs
        translatedAttVals =  translations->FindCompatibleAttValPairs(attVal);
        for (j = 0;j<translatedAttVals.size();j++)
        {
            attValStr = translatedAttVals[j].attribute + "," + translatedAttVals[j].value;
            compatibleAVPairs.insert(attValStr);
        }
        
        
    }
//testing///////////////////////
    
//    cerr << targetProfile->GetName() << endl << targetProfile ->GetEmail() << endl;
//    for (i = 0;i<targetAttVals.size();i++)
//        cerr << targetAttVals[i] << endl;
//    for  (auto it: compatibleAVPairs)
//    {
//        cerr << it << endl;
//    }
    // /////////////////////
    
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
            
            if (emailsMap.find(matchingEmails[i]) == emailsMap.end())
                // if the email has not already been added to the return map, add a new emailCount object with the email
            {
                emailsMap[matchingEmails[i]] = 1;
            }
            else
            {
                emailsMap.find(matchingEmails[i])->second++;
            }
        }
    }
    
    for (auto it: emailsMap)
    {
        if (it.second >= threshold)
        {
            compPerson.email = it.first;
            compPerson.count = it.second;
            comptPeople.push_back(compPerson);
        }
    }
    
    sort(comptPeople.begin(), comptPeople.end(), sortPeople);
    //loop through each the traits, find people that have those trait
    return comptPeople; //remember to return empty vector if no one is above threshold
}

bool MatchMaker::sortPeople(const EmailCount &a, const EmailCount &b)
{
    if (a.count >b.count)
        return true;
    else if (a.count <  b.count )
        return false;
    else
    {
        if (a.email < b.email)
            return true;
        else
            return false;
    }
}
