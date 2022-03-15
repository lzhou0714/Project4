////
////  AttributeTranslator.cpp
////  proj4
////
////  Created by Lily Zhou on 3/5/22.
////
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "AttributeTranslator.h"
using namespace std;
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
        if (transtr.size() == 0) //ignore empty lines
            continue;
        
        //split the line into source and compatible attval pairs
        firstCommaInd = transtr.find(',');
        secondCommaInd  = firstCommaInd + 1+ transtr.substr(firstCommaInd+1).find(',');
        source = transtr.substr(0,secondCommaInd);
        compatible = transtr.substr(secondCommaInd+1);
        existingTranslations = translations.search(source);
        
        if (existingTranslations == nullptr){ //source attval pair has not already been translated
            translations.insert(source, {compatible});
        }
        else{
            existingTranslations->push_back(compatible); //add to list of translations if source attval has already been translated
            translations.insert(source, *existingTranslations);
        }

    }

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
    for (int i  = 0;i < compatiblePair->size();i++) // add compatible attval pairs to return vector
    {
        int splitInd = (*compatiblePair)[i].find(',');
        inserts.attribute =(*compatiblePair)[i].substr(0,splitInd);
        inserts.value = (*compatiblePair)[i].substr(splitInd+1);
        if (find(results.begin(), results.end(),inserts)== results.end()){ //check for duplicates
            results.push_back(inserts);
        }
        
    }
    
    return results;
}
