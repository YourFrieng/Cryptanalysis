#pragma once
#include <string>
#include <vector>

std::wstring delete_rubish(const std::wstring& input);

std::wstring lower_case(std::wstring input);

std::wstring parse(const std::wstring& input);

//-------------------------GETTING TEXTS IN UKRAINIAN----------------
std::vector<std::wstring> GetLNTextsByFullText(const std::wstring& full_text, size_t L, size_t N);

std::wstring ReadUkrTextFromFile(std::string path);
