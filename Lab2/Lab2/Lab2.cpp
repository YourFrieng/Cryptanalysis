#include <iostream>

#include "GeneralInfo.h"
#include "AnalyseText.h"
#include "ReadingText.h"
#include "Criterias.h"

int main()
{
    std::wstring input = ReadUkrTextFromFile(/*"./Toreadory_z_Vasiukivky.txt"*//*"Kobzar.txt"*/"eneida.txt");
    //std::wcout << input << std::endl;
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
    
    std::wstring compessedInput = compressInput(input);
    ///ONE LETTER
    auto comp_text_size = compessedInput.size();
    auto comp_letters_count = letter_frequency(compessedInput);
    std::wcout << "Compressed Letter entropy: " << letter_entrop(comp_letters_count, comp_text_size) << std::endl;
    std::wcout << "Compressed Letter compliance index: " << letter_compliance_index(comp_letters_count, comp_text_size) << std::endl;

    ///BIGRAM
    auto comp_bigrams_count = bigram_count(compessedInput);
    auto comp_all_bigrams_count = bigram_sum(comp_bigrams_count);
    std::wcout << "Compressed Bigram entropy: " << bigram_entrop(comp_bigrams_count, comp_all_bigrams_count) << std::endl;
    std::wcout << "Compressed Bigram compliance index: " << bigram_compliance_index(comp_bigrams_count, comp_all_bigrams_count) << std::endl;

    //--------------GENERATED TEXT---------------------------

    std::wstring generatedText = GenerateText(input.size());
    auto gen_text_size = generatedText.size();
    auto gen_letters_count = letter_frequency(generatedText);
    std::wcout << "Generated Text Letter entropy: " << letter_entrop(gen_letters_count, gen_text_size) << std::endl;
    std::wcout << "Generated Text Letter compliance index: " << letter_compliance_index(gen_letters_count, gen_text_size) << std::endl;

    ///BIGRAM
    auto gen_bigrams_count = bigram_count(generatedText);
    auto gen_all_bigrams_count = bigram_sum(gen_bigrams_count);
    std::wcout << "Generated Text Bigram entropy: " << bigram_entrop(gen_bigrams_count, gen_all_bigrams_count) << std::endl;
    std::wcout << "Generated Text Bigram compliance index: " << bigram_compliance_index(gen_bigrams_count, gen_all_bigrams_count) << std::endl;

    std::wstring gen_compessedInput = compressInput(generatedText);
    ///ONE LETTER
    auto gen_comp_text_size = gen_compessedInput.size();
    auto gen_comp_letters_count = letter_frequency(gen_compessedInput);
    std::wcout << "Generated Compressed Letter entropy: " << letter_entrop(gen_comp_letters_count, gen_comp_text_size) << std::endl;
    std::wcout << "Generated Letter compliance index: " << letter_compliance_index(gen_comp_letters_count, gen_comp_text_size) << std::endl;

    ///BIGRAM
    auto gen_comp_bigrams_count = bigram_count(gen_compessedInput);
    auto gen_comp_all_bigrams_count = bigram_sum(gen_comp_bigrams_count);
    std::wcout << "Generated Compressed Bigram entropy: " << bigram_entrop(gen_comp_bigrams_count, gen_comp_all_bigrams_count) << std::endl;
    std::wcout << "Generated Compressed Bigram compliance index: " << bigram_compliance_index(gen_comp_bigrams_count, gen_comp_all_bigrams_count) << std::endl;

    ///Generating texts
    static std::map<size_t /*L*/, size_t /*N*/> LN_texts =
    {
        {10, 10000},
        {100, 10000},
        {1000, 10000},
        {10000, 1000}
    };

    std::vector<std::vector<std::wstring>> textesFromInput;
    for (const auto& L_N : LN_texts)
    {
        textesFromInput.push_back(GetLNTextsByFullText(input, L_N.first, L_N.second));
    }
}

