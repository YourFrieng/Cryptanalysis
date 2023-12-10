#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cwctype>
#include <map>
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

int main()
{
    setlocale(LC_ALL, "");
#ifdef _WIN32
    system("chcp 1251"); // setting up codecs
#endif

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    wstring input;
    string line;
    std::ifstream fin("./Toreadory_z_Vasiukivky..txt");
    while (getline(fin, line, '\n') && !line.empty())
    {
        input += converter.from_bytes(line);
    }
    fin.close();

    input = parse(input);
    wcout << input << endl;
}

