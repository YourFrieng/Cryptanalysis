#pragma once
#include <string>

//----------------------------DISTORTION OF THE TEXT-------------------
std::wstring cipherVigenere(const std::wstring& input, size_t r/*key size*/);

std::wstring cipherAfin(const std::wstring& input, size_t a, size_t b, size_t l);

std::wstring uniformDistrib(const std::wstring& input, size_t l);

std::wstring correlationGen(const std::wstring& input, size_t s0_num, size_t s1_num, size_t l);

