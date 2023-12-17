#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>

extern const std::map<wchar_t, wchar_t> lowercase;

extern const std::vector<wchar_t> alphabet;

size_t charNumbInAlph(wchar_t ch);
