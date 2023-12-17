#pragma once
#include <map>
#include <string>
#include <vector>
//-------------------------------FOR ONE LETTER------------------------

void output_frequency(const std::map<wchar_t, size_t>& letter_counter);

std::map <wchar_t, size_t> letter_frequency(const std::wstring& input);

double letter_probability(double text_size, double letter_count);

double entropy_term(double probability);

double letter_entrop(const std::map<wchar_t, size_t>& letters_count, size_t text_size);

double letter_compliance_index(const std::map<wchar_t, size_t>& letters_count, size_t text_size);

//-------------------------------FOR BIGRAMS------------------------
void output_bigram(const std::map<std::wstring, size_t>& bidram_counter);

std::map <std::wstring, size_t> bigram_count(const std::wstring& input);

size_t bigram_sum(const std::map<std::wstring, size_t>& bigrams);

double bigram_entrop(const std::map<std::wstring, size_t>& bigrams_count, size_t all_bigrams);

std::vector<std::wstring> generate_all_bigrams_on_alphabet();

double bigram_compliance_index(const std::map<std::wstring, size_t>& bigrams_count, size_t text_size);

double lgram_compliance_index(const std::map<std::wstring, size_t>& lgrams_count, size_t text_size, size_t l);
