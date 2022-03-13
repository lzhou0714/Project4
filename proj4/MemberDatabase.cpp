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
//            cout << dataString << endl;
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
            
//testing///////////////////////////////////////
            listEmails.push_back(email);
//testing///////////////////////////////////////
            
            m_numEmails++;
//            cerr << "profile: "  << m_numEmails << endl;
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
//                if (find(results->begin(), results->end(), email) ==results->end())
                if (avPairsTracker.find(dataString)  == avPairsTracker.end())
                {
                    avPairsTracker.insert(dataString);

                    results->push_back(email);
                    attValPairsToEmail.insert(dataString, *results);
                }

            }

//testing///////////////////////////////////////
//           listAttValPairs.insert(dataString);
//testing///////////////////////////////////////
            
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
    cerr << "profiles loaded: " << m_numEmails << endl;
    
//    for testing purposes

//    int i,j ;
//    AttValPair attvals;
//    for (i = 0;i<m_numEmails;i++ )
//    {
//        profile  = *emailToProfile.search(listEmails[i]);
//        cerr << profile->GetName() << endl;
//        cerr << profile->GetEmail() << endl;
//        for (j = 0;j<profile->GetNumAttValPairs();j++)
//        {
//            profile->GetAttVal(j, attvals);
//            cerr<< attvals.attribute << ","<< attvals.value;
//            cerr <<  endl;
//        }
//        cerr << endl;
//    }
//
//    for (auto it = listAttValPairs.begin(); it != listAttValPairs.end();it++)
//    {
//        cerr << *it << endl;
//        vector<string> emails = *attValPairsToEmail.search(*it);
//        for (auto it: emails)
//        {
//            cerr <<*(&it);
//            cerr <<endl;
//        }
//        cerr << endl;
//    }
////
    return true;
}
//
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
