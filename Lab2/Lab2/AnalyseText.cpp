#include "AnalyseText.h"
#include "GeneralInfo.h"
#include <iostream>

//-------------------------------FOR ONE LETTER------------------------

void output_frequency(const std::map<wchar_t, size_t>& letter_counter) {
    for (const auto& p : letter_counter) {
        std::wcout << L"letter: " << p.first << L" consized: " << p.second << std::endl;
    }
}

std::map <wchar_t, size_t> letter_frequency(const std::wstring& input) {
    std::map <wchar_t, size_t> let_counter;
    for (const auto& c : input) {
        ++let_counter[c];
    }

    output_frequency(let_counter);
    return let_counter;
}

double letter_probability(double text_size, double letter_count)
{
    return letter_count / text_size;
}

double entropy_term(double probability)
{
    return probability * log2(probability);
}

double letter_entrop(const std::map <wchar_t, size_t>& letters_count, size_t text_size)
{
    double result = 0;

    for (const auto& pair_let_count : letters_count)
    {
        auto probability = letter_probability(text_size, pair_let_count.second);
        result += entropy_term(probability);
    }

    result *= -1;

    return result;
}

double letter_compliance_index(const std::map <wchar_t, size_t>& letters_count, size_t text_size)
{
    double result = 0;
    for (auto alp_letter : alphabet)
    {
        auto it_letters_counter = letters_count.find(alp_letter);
        if (it_letters_counter != letters_count.end())
        {
            auto c_x = it_letters_counter->second; //letter count
            result += c_x * (c_x - 1);
        }
        else
            result += 0;
    }

    result /= text_size * (text_size - 1);
    return result;
}

//-------------------------------FOR BIGRAMS------------------------

void output_bigram(const std::map<std::wstring, size_t>& bidram_counter) {
    for (const auto& p : bidram_counter) {
        std::wcout << L"Bigram: " << p.first << L" consized " << p.second << std::endl;
    }
}

std::map <std::wstring, size_t> bigram_count(const std::wstring& input) {
    std::map <std::wstring, size_t> bigram_counter;
    for (int i = 0; i < input.length() - 1; i++) {

        ++bigram_counter[input.substr(i, 2)];
    }
    output_bigram(bigram_counter);
    return bigram_counter;
}

size_t bigram_sum(const std::map<std::wstring, size_t>& bigrams)
{
    size_t dick = 0;
    for (const auto& bigram : bigrams)
    {
        dick += bigram.second;
    }

    return dick;
}

double bigram_entrop(const std::map <std::wstring, size_t>& bigrams_count, size_t all_bigrams)
{
    double result = 0;

    for (const auto& pair_bigram_count : bigrams_count)
    {
        auto probability = letter_probability(all_bigrams, pair_bigram_count.second);
        result += entropy_term(probability);
    }

    result *= -1;

    return result / 2;
}

std::vector<std::wstring> generate_all_bigrams_on_alphabet()
{
    static std::vector<std::wstring> all_bigrams;
    if (!all_bigrams.empty())
        return all_bigrams;

    // generate all pairs in alphabet
    for (auto first : alphabet)
    {
        for (auto second : alphabet)
        {
            all_bigrams.push_back({ first, second });
        }
    }
    return all_bigrams;
}

double bigram_compliance_index(const std::map <std::wstring, size_t>& bigrams_count, size_t text_size)
{
    auto all_bigrams = generate_all_bigrams_on_alphabet();
    double result = 0;
    for (const auto& alp_letter : all_bigrams)
    {
        auto it_bigrams_counter = bigrams_count.find(alp_letter);
        if (it_bigrams_counter != bigrams_count.end())
        {
            auto c_x = it_bigrams_counter->second; //letter count
            result += c_x * (c_x - 1);
        }
        else
            result += 0;
    }

    result /= text_size * (text_size - 1);
    return result;
}

double lgram_compliance_index(const std::map<std::wstring, size_t>& lgrams_count, size_t text_size, size_t l)
{
    switch (l)
    {
    case 1:
    {
        std::map <wchar_t, size_t> letters_count;
        for (const auto& letter_freq_pair : lgrams_count)
            letters_count[letter_freq_pair.first[0]] = letter_freq_pair.second;
        return letter_compliance_index(letters_count, text_size);
    }
    case 2:
        return bigram_compliance_index(lgrams_count, text_size);
    default:
        break;
    }

    return 0;
}
