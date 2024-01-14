#include <iostream>
#include <fstream>

#include "GeneralInfo.h"
#include "AnalyseText.h"
#include "ReadingText.h"
#include "Criterias.h"
#include "Distortion.h"
#include <array>

int main()
{
    std::wstring input = ReadUkrTextFromFile("./Toreadory_z_Vasiukivky.txt"/*"Kobzar.txt"*//*"eneida.txt"*/);
    //std::wcout << input << std::endl;
    ///ONE LETTER
    auto text_size = input.size();
    auto letters_count_universal = CreateUniformFrequency(input, 1);
    auto letters_count = letter_frequency(input);
    std::wcout << "Letter entropy: " << letter_entrop(letters_count, text_size) << std::endl;
    double letter_CI = letter_compliance_index(letters_count, text_size);
    std::wcout << "Letter compliance index: " << letter_CI  << std::endl;
    //TOP/RARE LETTERS
#if 0
    std::map<size_t, std::wstring> top_letters;
    for (const auto& letter_and_it_count : letters_count)
        top_letters[letter_and_it_count.second] = letter_and_it_count.first;
    std::wcout << "Top bigrams: " << std::endl;
    for (const auto& count_and_letter : letters_count)
        std::wcout << "{" << count_and_letter.first << ", \"" << count_and_letter.second << "\"}" << std::endl;

    size_t i = 0;
    std::wcout << "{";
    for (auto rit = top_letters.rbegin(); rit != top_letters.rend(); rit++)
    {
        if (i > 9)
            break;
        std::wcout << "\"" << rit->second << "\",";
        ++i;
    }
    std::wcout << "\"}" << std::endl;

    i = 0;
    std::vector<std::wstring> rare_letters;
    for (const auto& count_and_letter : top_letters)
    {
        if (i >= 5)
            break;
        rare_letters.push_back(count_and_letter.second);
        ++i;
    }

    std::wcout << "{";
    for (const auto& rare_bigram : rare_letters)
    {
        std::wcout << "L\"" << rare_bigram << "\",";
    }
    std::wcout << "\"}" << std::endl;
#endif
    ///BIGRAM
    auto bigrams_count = bigram_count(input);
    auto all_bigrams_count = bigram_sum(bigrams_count);
    std::wcout << "Bigram entropy: " << bigram_entrop(bigrams_count, all_bigrams_count) << std::endl;
    double bigram_CI = bigram_compliance_index(bigrams_count, all_bigrams_count);
    std::wcout << "Bigram compliance index: " << bigram_CI << std::endl;
    //TOP/RARE BIGRAMS
#if 0
    std::map<size_t, std::wstring> top_bigrams;
    for (const auto& bigram_and_it_count : bigrams_count)
        top_bigrams[bigram_and_it_count.second] = bigram_and_it_count.first;
    std::wcout << "Top bigrams: " << std::endl;
    for (const auto& count_and_bigram : top_bigrams)
        std::wcout << "{" << count_and_bigram.first << ", \"" << count_and_bigram.second << "\"}" << std::endl;

    size_t i = 0;
    std::wcout << "{";
    for (auto rit = top_bigrams.rbegin(); rit != top_bigrams.rend(); rit++)
    {
        std::wcout << "\"" << rit->second << "\",";
        if (i > 15)
            break;
        ++i;
    }
    std::wcout << "\"}" << std::endl;

    auto allBigrams = generate_all_bigrams_on_alphabet();
    std::vector<std::wstring> rare_bigrams;
    std::copy_if(allBigrams.begin(), allBigrams.end(), std::back_inserter(rare_bigrams),
        [&bigrams_count](const std::wstring& arg)
        {
            auto foundBigram = bigrams_count.find(arg);
            return ((foundBigram == bigrams_count.end()) || (foundBigram->second < 100));
        });

    i = 0;
    std::wcout << "{";
    for (const auto& rare_bigram : rare_bigrams)
    {
        std::wcout << "L\"" << rare_bigram << "\",";
        if (i > 200)
            break;
        ++i;
    }
    std::wcout << "\"}" << std::endl;
#endif
#if 0
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
#endif
    //--------------GENERATED TEXT---------------------------
#if 0
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
#endif
    ///Generating texts
    static std::map<size_t /*L*/, size_t /*N*/> LN_texts =
    {
        {10, 10000},
        {100, 10000},
        {1000, 10000},
        {10000, 1000}
    };
    //Original text
#if 0
    std::map<size_t /*L*/, std::vector<std::wstring>> textesFromInput;
    std::map<size_t /*L*/, std::vector<std::vector<std::wstring>>> YtextesFromInput;
    for (const auto& L_N : LN_texts)
    {
        textesFromInput[L_N.first] = GetLNTextsByFullText(input, L_N.first, L_N.second);
        const auto& openTextes = textesFromInput[L_N.first];
#if 0
        std::vector<std::vector<std::wstring>> allCipherTextesFor1;
        allCipherTextesFor1.reserve(openTextes.size());
        for (const auto& text : openTextes)
        {
            std::vector<std::wstring> cipherTextes;
            cipherTextes.reserve(9);
            ///Vigenere
            //r=1
            cipherTextes.push_back(cipherVigenere(text, 1));
            //r=5
            cipherTextes.push_back(cipherVigenere(text, 5));
            //r=10
            cipherTextes.push_back(cipherVigenere(text, 10));

            ///Afin
            std::srand(std::time(nullptr)); // use current time as seed for random generator
            size_t a = std::rand() % 10;
            size_t b = std::rand() % 10;
            cipherTextes.push_back(cipherAfin(text, a, b, 1));
            cipherTextes.push_back(cipherAfin(text, a, b, 2));

            ///Uniform
            cipherTextes.push_back(uniformDistrib(text, 1));
            cipherTextes.push_back(uniformDistrib(text, 2));

            ///correlation
            cipherTextes.push_back(correlationGen(text, 3, 6, 1));
            cipherTextes.push_back(correlationGen(text, 3, 6, 2));

            allCipherTextesFor1.push_back(std::move(cipherTextes));
        }
        YtextesFromInput[L_N.first] = std::move(allCipherTextesFor1);
#endif
    }
#endif
    auto generatedText = GenerateText(10000);
    auto cipherGenText = cipherVigenere(generatedText, 5);
    switch (criterionStructure(cipherGenText, 0.27f)/*criterionConformityIndex(cipherGenText, letter_CI, 0.05f, 1)*/)
    {
    case HYPOTHESIS::H_0:
        std::wcout << "H_0" << std::endl;
        break;
    case HYPOTHESIS::H_1:
        std::wcout << "H_1" << std::endl;
        break;
    }
#if 0
    std::wofstream fout("results.txt");
    for (const auto& L_N : LN_texts)
    {
        fout << "CRITERIAS FOR TEXT LEN:" << L_N.first << std::endl;
        //fout << "-------------CRITERIAS ON OPEN TEXT--------------" << std::endl;
        std::array<size_t, 13> H_0_count = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
        std::array<size_t, 13> H_1_count = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

        for (const auto& openText : textesFromInput.at(L_N.first))
        {
            switch (criterionFrequentLgrams0(openText, theMostLetters, 1))
            {
            case HYPOTHESIS::H_0:
                H_0_count[0]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[0]++;
                break;
            }

            switch (criterionFrequentLgrams0(openText, theMostBigrams, 2))
            {
            case HYPOTHESIS::H_0:
                H_0_count[1]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[1]++;
                break;
            }

            switch (criterionFrequentLgrams1(openText, theMostLetters, 1, 4))
            {
            case HYPOTHESIS::H_0:
                H_0_count[2]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[2]++;
                break;
            }

            switch (criterionFrequentLgrams1(openText, theMostBigrams, 2, 4))
            {
            case HYPOTHESIS::H_0:
                H_0_count[3]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[3]++;
                break;
            }

            switch (criterionFrequentLgrams2(openText, letters_count_universal, 1, 4))
            {
            case HYPOTHESIS::H_0:
                H_0_count[4]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[4]++;
                break;
            }

            switch (criterionFrequentLgrams2(openText, bigrams_count, 2, 4))
            {
            case HYPOTHESIS::H_0:
                H_0_count[5]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[5]++;
                break;
            }

            switch (criterionFrequentLgrams3(openText, letters_count_universal, 1))
            {
            case HYPOTHESIS::H_0:
                H_0_count[6]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[6]++;
                break;
            }

            switch (criterionFrequentLgrams3(openText, bigrams_count, 2))
            {
            case HYPOTHESIS::H_0:
                H_0_count[7]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[7]++;
                break;
            }

            switch (criterionConformityIndex(openText, letter_CI, 0.05f, 1))
            {
            case HYPOTHESIS::H_0:
                H_0_count[8]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[8]++;
                break;
            }

            switch (criterionConformityIndex(openText, bigram_CI, 0.05f, 2))
            {
            case HYPOTHESIS::H_0:
                H_0_count[9]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[9]++;
                break;
            }

            switch (criterionEmptyBoxes(openText, theRareLetters, 4, 1))
            {
            case HYPOTHESIS::H_0:
                H_0_count[10]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[10]++;
                break;
            }

            switch (criterionEmptyBoxes(openText, theRareBigrams, 4, 2))
            {
            case HYPOTHESIS::H_0:
                H_0_count[11]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[11]++;
                break;
            }

            switch (criterionStructure(openText, 0.27f))
            {
            case HYPOTHESIS::H_0:
                H_0_count[12]++;
                break;
            case HYPOTHESIS::H_1:
                H_1_count[12]++;
                break;
            }
        }

        for (size_t i = 0; i < 13; i++)
        {
            fout << "H_0 count: " << H_0_count[i] << std::endl;
            fout << "H_1 count: " << H_1_count[i] << std::endl;
        }
    }
#endif
#if 0 
    for (const auto& L_N : LN_texts)
    {
        fout << "CRITERIAS FOR TEXT LEN:" << L_N.first << std::endl;
        //fout << "-------------CRITERIAS ON OPEN TEXT--------------" << std::endl;
        std::array<size_t, 13> H_0_count = {0,0,0,0,0,0,0,0,0,0,0,0,0};
        std::array<size_t, 13> H_1_count = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };;
        for (const auto& cipherTextes : YtextesFromInput.at(L_N.first))
        {
            for (const auto& cipherText : cipherTextes)
            {
                switch (criterionFrequentLgrams0(cipherText, theMostLetters, 1))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[0]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[0]++;
                    break;
                }

                switch (criterionFrequentLgrams0(cipherText, theMostBigrams, 2))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[1]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[1]++;
                    break;
                }

                switch (criterionFrequentLgrams1(cipherText, theMostLetters, 1, 4))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[2]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[2]++;
                    break;
                }

                switch (criterionFrequentLgrams1(cipherText, theMostBigrams, 2, 4))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[3]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[3]++;
                    break;
                }

                switch (criterionFrequentLgrams2(cipherText, letters_count_universal, 1, 4))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[4]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[4]++;
                    break;
                }

                switch (criterionFrequentLgrams2(cipherText, bigrams_count, 2, 4))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[5]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[5]++;
                    break;
                }

                switch (criterionFrequentLgrams3(cipherText, letters_count_universal, 1))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[6]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[6]++;
                    break;
                }

                switch (criterionFrequentLgrams3(cipherText, bigrams_count, 2))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[7]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[7]++;
                    break;
                }

                switch (criterionConformityIndex(cipherText, letter_CI, 0.05f, 1))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[8]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[8]++;
                    break;
                }

                switch (criterionConformityIndex(cipherText, bigram_CI, 0.05f, 2))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[9]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[9]++;
                    break;
                }

                switch (criterionEmptyBoxes(cipherText, theRareLetters, 4, 1))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[10]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[10]++;
                    break;
                }

                switch (criterionEmptyBoxes(cipherText, theRareBigrams, 4, 2))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[11]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[11]++;
                    break;
                }

                switch (criterionStructure(cipherText, 0.27f))
                {
                case HYPOTHESIS::H_0:
                    H_0_count[12]++;
                    break;
                case HYPOTHESIS::H_1:
                    H_1_count[12]++;
                    break;
                }
            }
        }

        for (size_t i = 0; i < 13; i++)
        {
            fout << "H_0 count: " << H_0_count[i] << std::endl;
            fout << "H_1 count: " << H_1_count[i] << std::endl;
        }
    }
#endif
    //fout.close();
}

