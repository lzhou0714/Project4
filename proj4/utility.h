//
//  utility.hpp
//  proj4
//
//  Created by Lily Zhou on 3/5/22.
//



#ifndef RADIX_UTILITY_H
#define RADIX_UTILITY_H

#include "provided.h"
#include <string>

std::string AVPairToString(const AttValPair& convert) {
    return convert.attribute + "," + convert.value;
}

#endif //RADIX_UTILITY_H
