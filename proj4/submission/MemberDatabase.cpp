//
//  MemberDatabase.cpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//
#include <iostream>
#include <fstream>
#include <string>
#include "MemberDatabase.h"
using namespace std;

MemberDatabase::~MemberDatabase()
{
    for (int i =0;i<vectProfiles.size();i++)
        delete vectProfiles[i];
}
bool MemberDatabase::LoadDatabase(string filename)
{
    std::ifstream dataFile;
    dataFile.open(filename);
    
    string dataString;
    string name = "";
    string email = "";
    int remainingAtt = 0;
    set<string> avPairsTracker;
    PersonProfile* profile;

    if ( !dataFile.is_open() )
        return false;
    while (std::getline(dataFile,dataString))
    {
        if (dataString.empty())
        {
            name = "";
            email = "";
            remainingAtt = 0;
        }
        if (name.empty())
        {
            name = dataString;
        }
        else if (email.empty())
        {
            email = dataString;

            if (emailToProfile.search(email) !=nullptr) //email already entered
                return false;
            profile = new PersonProfile(name, email);
            m_numEmails++;
        }
        else if (isdigit(dataString[0]))//attval pairs
        {
            remainingAtt = stoi(dataString);
        }
        else if  (remainingAtt >0)
        {

            vector<string>* results = attValPairsToEmail.search(dataString);
            if(results == nullptr) {
                attValPairsToEmail.insert(dataString, {email});
                avPairsTracker.insert(dataString);

            } else {
                if (avPairsTracker.find(dataString)  == avPairsTracker.end())
                {
                    avPairsTracker.insert(dataString);

                    results->push_back(email);
                    attValPairsToEmail.insert(dataString, *results);
                }
            }
            
           m_numAttValPairs++;
                       
           //update tree with emails to personal profiles
           int ind  = dataString.find(',');
           AttValPair newPair(dataString.substr(0,ind), dataString.substr(ind+1));
           profile->AddAttValPair(newPair);
           remainingAtt--;
           if (remainingAtt ==0)
           {
               emailToProfile.insert(email, profile);
               vectProfiles.push_back(profile);
               avPairsTracker.clear();

           }

        }
        
    }
    dataFile.close();
    return true;
}

const PersonProfile* MemberDatabase:: GetMemberByEmail(string email)const
{
    if (emailToProfile.search(email) == nullptr)
        return nullptr;
    else return *emailToProfile.search(email);
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string aVString  = input.attribute + "," + input.value;
    vector<string>* emails = attValPairsToEmail.search(aVString);
    if (emails != nullptr)
    {
        return *emails;
    }
    else
    {
        vector<string> empty;
        return empty;
    }

        
}
