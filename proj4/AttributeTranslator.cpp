////
////  AttributeTranslator.cpp
////  proj4
////
////  Created by Lily Zhou on 3/5/22.
////
//
#include <iostream>
#include <fstream>
#include <string>

#include "AttributeTranslator.h"
bool AttributeTranslator::Load(string filename)
{
    std::ifstream tranFile;
    tranFile.open(filename);
    
    string transtr;
    if (!tranFile.is_open())
        return false;
    int firstCommaInd;
    int secondCommaInd;
    string source;
    string compatible;
    vector<string>* existingTranslations;
    while (std::getline(tranFile, transtr))
    {
        if (transtr.size() == 0)
            continue;
        firstCommaInd = transtr.find(',');
        secondCommaInd  = firstCommaInd + 1+ transtr.substr(firstCommaInd+1).find(',');
        source = transtr.substr(0,secondCommaInd);
        compatible = transtr.substr(secondCommaInd+1);
//        cerr << source<< ","<< compatible <<endl;
        existingTranslations = translations.search(source);
        if (existingTranslations == nullptr){ //source attval pair not in radix tree
            translations.insert(source, {compatible});
        }
        else{
            existingTranslations->push_back(compatible);
            translations.insert(source, *existingTranslations);
        }
        //testing///////////////
        sources.insert(source);
        // ///////////////////////////////
    }
    
//testing ////////////////////////////////
//    for (auto it1: sources)
//    {
//        existingTranslations = translations.search(it1);
//        cerr<< it1 << "~~"<<endl;
//        for (int i = 0;i<existingTranslations->size();i++)
//        {
//            cerr << i+1<<":" <<(*existingTranslations)[i] << endl;
//        }
//        cerr <<  endl;
//    }
// /////////////////////////////////////////
    return true;
}

vector<AttValPair> AttributeTranslator:: FindCompatibleAttValPairs(const AttValPair& source) const
{
    string sourceStr = source.attribute +","+source.value;
    vector<string>* compatiblePair = translations.search(sourceStr);
    vector<AttValPair>results;

    if (compatiblePair == nullptr)
        return results;
    AttValPair inserts;
    for (int i  = 0;i < compatiblePair->size();i++)
    {
        int splitInd = (*compatiblePair)[i].find(',');
        inserts.attribute =(*compatiblePair)[i].substr(0,splitInd);
//        cerr << inserts.attribute << endl;
        inserts.value = (*compatiblePair)[i].substr(splitInd+1);
//        cerr << inserts.value << endl;
        if (find(results.begin(), results.end(),inserts)== results.end()){
            
            results.push_back(inserts);
        }
        
    }
    
    return results;
}
