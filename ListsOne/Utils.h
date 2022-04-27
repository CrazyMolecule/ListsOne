#ifndef UTILS_H
#define UTILS_H
#include "ForwardList.h"

using namespace bavykin;

forward_list< std::string > splitString(const std::string& str, const std::string& delimiter);
#endif
