#include "ReadingText.h"
#include "GeneralInfo.h"
#include <sstream>
#include <codecvt>
#include <fstream>
#include <cstdlib>
#include <ctime>

std::wstring delete_rubish(const std::wstring& input)
{
    std::wstring result;
    for (const auto& c : input) {
        if (lowercase.find(c) != lowercase.end()) {
            result.push_back(c);
        }
    }
    return result;
}

std::wstring lower_case(std::wstring input)
{
    for_each(input.begin(), input.end(), [&](wchar_t& c) {c = lowercase.at(c); });
    return input;
}

std::wstring parse(const std::wstring& input) {

    auto low_input = lower_case(delete_rubish(input));
    std::wstringstream ss;
    ss << low_input;
    std::wstring buf, result;
    while (!ss.eof())
    {
        ss >> buf;
        auto c = ss.peek();
        do {
            ss.ignore(1);
            c = ss.peek();
        } while (c == L' ');
        result += buf;
    }
    result.erase(result.end() - 1);
    return result;
}

//-------------------------GETTING TEXTS IN UKRAINIAN----------------

/**
 * Breaks the text into N texts with L letters in each text.
 *
 * @param full_text -input text without rubbish and lowercased
 * @param L - count of letters in got text
 * @param N - count of texts
 * @return vector of N texts(text size is L)
 */
std::vector<std::wstring> GetLNTextsByFullText(const std::wstring& full_text, size_t L, size_t N)
{
    std::vector<std::wstring> n_texts(N, std::wstring(L, ' '));
    auto it_n_texts = n_texts.begin();
    for (size_t i = 0; i < N; i += L)
    {
        if (i + L > full_text.size())
            break;

        *it_n_texts = full_text.substr(i, L);
        it_n_texts = std::next(it_n_texts);
    }
    return n_texts;
}

std::wstring GenerateText(size_t text_len)
{
    std::wstring generatedText;
    generatedText.reserve(text_len);
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    for (size_t i = 0; i < text_len; i++)
        generatedText.push_back(alphabet[std::rand() % alphabet.size()]);

    return generatedText;
}

std::wstring ReadUkrTextFromFile(std::string path)
{
    setlocale(LC_ALL, "");
#ifdef _WIN32
    system("chcp 1251"); // setting up codecs
#endif

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring input;
    std::string line;
    std::ifstream fin(path);
    while (std::getline(fin, line, '\n')/* && !line.empty()*/)
    {
        input += converter.from_bytes(line);
    }
    fin.close();

    input = parse(input);

    return input;
}
