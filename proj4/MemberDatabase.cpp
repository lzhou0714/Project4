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
bool MemberDatabase::LoadDatabase(string filename)
{
    std::ifstream dataFile;
    dataFile.open(filename);
    
    string dataString;
    string name = "";
    string email = "";
    int remainingAtt = 0;
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
//            continue;
        }
        if (name.empty())
        {
            name = dataString;
//            continue;
        }
        else if (email.empty())
        {
            email = dataString;

            if (emailToProfile.search(email) !=nullptr) //email already entered
                return false;
            profile = new PersonProfile(name, email);
//            emailToProfile.insert(email, profile);
            listEmails.push_back(email);
            m_numEmails++;
//            cerr << "profile: "  << m_numEmails << endl;

        }
        else if (isdigit(dataString[0]))//attval pairs
        {
            remainingAtt = stoi(dataString);
        }
        else if  (remainingAtt >0)
        {
            //update tree of aVpairs to emails
            vector<string>* results = attValPairsToEmail.search(dataString);
            if(results == nullptr) {
                attValPairsToEmail.insert(dataString, {email});
            } else {
                results->push_back(email);
                attValPairsToEmail.insert(dataString, *results);
            }

//            listAttValPairs.insert(dataString);
            m_numAttValPairs++;
            
            //update tree with emails to personal profiles
            int ind  = dataString.find(',');
            AttValPair newPair(dataString.substr(0,ind), dataString.substr(ind+1));
            profile->AddAttValPair(newPair);
            remainingAtt--;
            if (remainingAtt ==0)
            {
                emailToProfile.insert(email, profile);
            }
        }
        
    }
    dataFile.close();
    
    
    //for testing purposes
//
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
//        setOfEmails = *attValPairsToEmail.search(*it);
//        for (auto it: setOfEmails)
//        {
//            cerr <<*(&it);
//            cerr <<endl;
//        }
//        cerr << endl;
//    }

    return true;
}
