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
    set<string> setOfEmails;
    PersonProfile* profile;

    if ( !dataFile.is_open() )
        return false;
    while (std::getline(dataFile,dataString))
    {
        setOfEmails.clear();
//            cout << dataString << endl;
        if (dataString.size() == 0)
        {
            name = "";
            email = "";
            remainingAtt = 0;
            continue;
        }
        if (name.empty())
        {
            name = dataString;
            continue;
        }
        if (email.empty())
        {
            email = dataString;
            if (emailToProfile.search(email) !=nullptr) //email already entered
                return false;
            profile = new PersonProfile(name, email);
            emailToProfile.insert(email, profile);
            listEmails.push_back(email);
            m_numEmails++;
            cerr << "profile: "  << m_numEmails << endl;

            continue;
        }
        else if (isdigit(dataString[0]))//attval pairs
        {
            remainingAtt = stoi(dataString);
        }
        else if  (remainingAtt >0)
        {
            //update tree of aVpairs to emails
            set<string>* emailSetptr  = attValPairsToEmail.search(dataString);
            if ( emailSetptr != nullptr) //try tracking and finding with a set if tree is too slow
            {
                setOfEmails = *emailSetptr;
            }
            setOfEmails.insert(email);
            attValPairsToEmail.insert(dataString, setOfEmails);
            listAttValPairs.insert(dataString);
            m_numAttValPairs++;
            
            //update tree with emails to personal profiles
            PersonProfile* profile = *emailToProfile.search(email);
            if (profile!=nullptr)
            {
                int ind  = dataString.find(',');
                AttValPair newPair(dataString.substr(0,ind), dataString.substr(ind+1));
                profile->AddAttValPair(newPair);
                
            }
        }
    }
    dataFile.close();
    
    
    //for testing purposes
    
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
