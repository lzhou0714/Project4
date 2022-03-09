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
    int newPerson  = 1;
    string name = "";
    string email = "";
    set<string> setOfEmails;
    PersonProfile* profile;

    if ( dataFile.is_open() ) { // always check whether the file is open
        while (dataFile)
        {
            setOfEmails.clear();

            std::getline(dataFile,dataString);
//            cout << dataString << endl;
            if (dataString.size() == 0)
            {
                newPerson = 1;
                continue;
            }
            else if (newPerson ==1 )
            {
                name = dataString;
                newPerson++;
                continue;
            }
            else if (newPerson ==2)
            {
                email = dataString;
                newPerson++;
                if (emailToProfile.search(email) !=nullptr)
                    return false;
                profile = new PersonProfile(name, email);
                emailToProfile.insert(email, *profile);
                listEmails.push_back(email);
                m_numEmails++;
                continue;
            }
            else if (newPerson == 3) // # of att val pairs
            {
                newPerson = 0;
                continue;
            }
            else //attval pairs
            {
                //update tree of aVpairs to emails
                set<string>* emailSetptr  = attValPairsToEmail.search(dataString);
                if ( emailSetptr != nullptr) //try tracking and finding with a set if tree is too slow
                {
                    setOfEmails = *emailSetptr;
                }

//                    setOfEmails.clear();
                setOfEmails.insert(email);
                attValPairsToEmail.insert(dataString, setOfEmails);
                listAttValPairs.insert(dataString);
                m_numAttValPairs++;
                
                //update tree with emails to personal profiles
                PersonProfile* profile = emailToProfile.search(email);
                if (profile!=nullptr)
                {
                    int i;
                    for (i = 0; i<dataString.size();i++)
                    {
                        if (dataString[i] == ',')
                            break;
                    }
                    AttValPair newPair(dataString.substr(0,i), dataString.substr(i+1));
                    profile->AddAttValPair(newPair);
                    
                }

            }
//            std::cout << dataString; // pipe stream's content to standard output
        }
    }
    dataFile.close();
    
    
    //for testing purposes
    
    int i,j ;
    AttValPair attvals;
//    for (i = 0;i<m_numEmails;i++ )
//    {
//        profile  = emailToProfile.search(listEmails[i]);
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
