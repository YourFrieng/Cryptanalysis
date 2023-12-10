#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cwctype>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <locale>
#include <codecvt>

using namespace std;

const map<wchar_t, wchar_t> lowercase =
{
    {L'А',L'а'},
    {L'Б',L'б'},
    {L'В',L'в'},
    {L'Г',L'г'},
    {L'Ґ',L'г'},
    {L'Д',L'д'},
    {L'Е',L'е'},
    {L'Ж',L'ж'},
    {L'З',L'з'},
    {L'И',L'и'},
    {L'І',L'і'},
    {L'Ї',L'ї'},
    {L'Й',L'й'},
    {L'К',L'к'},
    {L'Л',L'л'},
    {L'М',L'м'},
    {L'Н',L'н'},
    {L'О',L'о'},
    {L'П',L'п'},
    {L'Р',L'р'},
    {L'С',L'с'},
    {L'Т',L'т'},
    {L'У',L'у'},
    {L'Ф',L'ф'},
    {L'Х',L'х'},
    {L'Ц',L'ц'},
    {L'Ч',L'ч'},
    {L'Ш',L'ш'},
    {L'Щ',L'щ'},
    {L'Ь',L'ь'},
    {L'Ю',L'ю'},
    {L'Я',L'я'},
    {L'а',L'а'},
    {L'б',L'б'},
    {L'в',L'в'},
    {L'г',L'г'},
    {L'ґ',L'г'},
    {L'д',L'д'},
    {L'е',L'е'},
    {L'ж',L'ж'},
    {L'з',L'з'},
    {L'и',L'и'},
    {L'і',L'і'},
    {L'ї',L'ї'},
    {L'й',L'й'},
    {L'к',L'к'},
    {L'л',L'л'},
    {L'м',L'м'},
    {L'н',L'н'},
    {L'о',L'о'},
    {L'п',L'п'},
    {L'р',L'р'},
    {L'с',L'с'},
    {L'т',L'т'},
    {L'у',L'у'},
    {L'ф',L'ф'},
    {L'х',L'х'},
    {L'ц',L'ц'},
    {L'ч',L'ч'},
    {L'ш',L'ш'},
    {L'щ',L'щ'},
    {L'ь',L'ь'},
    {L'ю',L'ю'},
    {L'я',L'я'}
};

const set<wchar_t> alphabet =
{ L'а',L'б',L'в',L'г',L'ґ',L'д',L'е',L'ж',L'з',L'и',L'і',L'ї',L'й',L'к',L'л',L'м',L'н',L'о',L'п',L'р',L'с',L'т',L'у',L'ф',L'х',L'ц',L'ч',L'ш',L'щ',L'ь',L'ю', L'я' };

wstring delete_rubish(const wstring& input) {
    wstring result;
    for (const auto& c : input) {
        if (lowercase.find(c) != lowercase.end()) {
            result.push_back(c);
        }
    }
    return result;
}

wstring lower_case(wstring input) {
    input = delete_rubish(input);
    for_each(input.begin(), input.end(), [&](wchar_t& c) {c = lowercase.at(c); });
    return input;
}
wstring parse(const wstring& input) {

    wstring low_input = lower_case(input);
    wstringstream ss;
    ss << low_input;
    wstring buf, result;
    while (!ss.eof())
    {
        ss >> buf;
        auto c = ss.peek();
        do {
            ss.ignore(1);
            c = ss.peek();
        } while (c == L' ');
        result += buf + L' ';
    }
    result.erase(result.end() - 1);
    return result;
}

//-------------------------------FOR ONE LETTER------------------------

void output_frequency(const map<wchar_t, size_t>& letter_counter) {
    for (const auto& p : letter_counter) {
        wcout << L"letter: " << p.first << L" consized: " << p.second << endl;
    }
}

auto letter_frequency(const wstring& input) {
    map <wchar_t, size_t> let_counter;
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

double letter_entrop(const map <wchar_t, size_t>& letters_count, size_t text_size)
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

double letter_compliance_index(const map <wchar_t, size_t>& letters_count, size_t text_size)
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
void output_bigram(const map<wstring, size_t>& bidram_counter) {
    for (const auto& p : bidram_counter) {
        wcout << L"Bigram: " << p.first << L" consized " << p.second << endl;
    }
}

auto bigram_count(wstring input) {
    map <wstring, size_t> bigram_counter;
    for (int i = 0; i < input.length() - 1; i++) {

        ++bigram_counter[input.substr(i, 2)];
    }
    output_bigram(bigram_counter);
    return bigram_counter;
}

size_t bigram_sum(const map<wstring, size_t>& bigrams)
{
    size_t dick = 0;
    for (const auto& bigram : bigrams)
    {
        dick += bigram.second;
    }

    return dick;
}

double bigram_entrop(const map <wstring, size_t>& bigrams_count, size_t all_bigrams)
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

std::set<wstring> generate_all_bigrams_on_alphabet()
{
    std::set<wstring> all_bigrams;
    // generate all pairs in alphabet
    for (auto first : alphabet) 
    {
        for (auto second : alphabet) 
        {
            all_bigrams.insert({ first, second });
        }
    }
    return all_bigrams;
}

double bigram_compliance_index(const map <wstring, size_t>& bigrams_count, size_t text_size)
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


int main()
{
    setlocale(LC_ALL, "");
#ifdef _WIN32
    system("chcp 1251"); // setting up codecs
#endif

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    wstring input;
    string line;
    std::ifstream fin("./Toreadory_z_Vasiukivky.txt");
    while (getline(fin, line, '\n') && !line.empty())
    {
        input += converter.from_bytes(line);
    }
    fin.close();

    input = parse(input);
    wcout << input << endl;

    ///ONE LETTER
    auto text_size = input.size();
    auto letters_count = letter_frequency(input);
    wcout << "Letter entropy: " << letter_entrop(letters_count, text_size) << std::endl;
    wcout << "Letter compliance index: " << letter_compliance_index(letters_count, text_size) << std::endl;
    
    ///BIGRAM
    auto bigrams_count = bigram_count(input);
    auto all_bigrams_count = bigram_sum(bigrams_count);
    wcout << "Bigram entropy: " << bigram_entrop(bigrams_count, all_bigrams_count) << std::endl;
    wcout << "Bigram compliance index: " << bigram_compliance_index(bigrams_count, all_bigrams_count) << std::endl;
}

