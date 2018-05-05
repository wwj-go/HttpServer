#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>


std::vector<std::string> split(std::string str, std::string pattern);

int getGmtTime(char* szGmtTime);

string getType(string ext);
#endif 