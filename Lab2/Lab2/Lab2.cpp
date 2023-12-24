#include <iostream>

#include "GeneralInfo.h"
#include "AnalyseText.h"
#include "ReadingText.h"
#include "Criterias.h"

int main()
{
    std::wstring input = ReadUkrTextFromFile("./Toreadory_z_Vasiukivky.txt");
    std::wcout << input << std::endl;
    ///ONE LETTER
    auto text_size = input.size();
    auto letters_count = letter_frequency(input);
    std::wcout << "Letter entropy: " << letter_entrop(letters_count, text_size) << std::endl;
    std::wcout << "Letter compliance index: " << letter_compliance_index(letters_count, text_size) << std::endl;
    
    ///BIGRAM
    auto bigrams_count = bigram_count(input);
    auto all_bigrams_count = bigram_sum(bigrams_count);
    std::wcout << "Bigram entropy: " << bigram_entrop(bigrams_count, all_bigrams_count) << std::endl;
    std::wcout << "Bigram compliance index: " << bigram_compliance_index(bigrams_count, all_bigrams_count) << std::endl;

    ///Generating texts
    static std::map<size_t /*L*/, size_t /*N*/> LN_texts =
    {
        {10, 10000},
        {100, 10000},
        {1000, 10000},
        {10000, 1000}
    };
    for (const auto& L_N : LN_texts)
    {
        GetLNTextsByFullText(input, L_N.first, L_N.second);
    }
}

