#include "Distortion.h"
#include "GeneralInfo.h"
#include "AnalyseText.h"
#include <random>
#include <cmath>

std::wstring cipherVigenere(const std::wstring& input, size_t r/*key size*/)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    auto m = alphabet.size();
    std::uniform_int_distribution<> distrib(0, m);

    ///Generate rand key
    std::vector<size_t> randKey;
    randKey.reserve(r);
    for (size_t i = 0; i < r; i++)
        randKey.push_back(distrib(gen));

    ///distort text
    std::wstring cipher_text;
    cipher_text.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++)
        cipher_text.push_back(alphabet.at((charNumbInAlph(input[i]) + randKey[i % r]) % m));

    return cipher_text;
}

size_t gcd(size_t a, size_t b) {
    while (b != 0)
    {
        size_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::wstring cipherAfin(const std::wstring& input, size_t a, size_t b, size_t l)
{
    ///distort text
    std::wstring cipher_text;
    cipher_text.reserve(input.size());
    auto m = alphabet.size();
    size_t m_pow_l = std::pow(m, l);
    for (size_t i = 0; i < input.size(); i += l)
    {
        size_t l_copy = l + 1;
        size_t x_i = 0;
        while (l_copy >= 0)
        {
            x_i = charNumbInAlph(input[i]) * std::pow(m, --l_copy);
        }

        cipher_text.push_back((a * x_i + b) % m_pow_l);
    }

    return cipher_text;
}

std::wstring uniformDistrib(const std::wstring& input, size_t l)
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::vector<std::wstring> all_bigrams;
    if (l == 2)
    {
        all_bigrams = generate_all_bigrams_on_alphabet();
    }
    std::uniform_int_distribution<> distrib(0, (l == 1) ? alphabet.size() - 1 : all_bigrams.size() - 1);
    std::wstring Y;
    Y.reserve(input.size());
    for (size_t i = 0; i < (input.size() / l); i++)
    {
        if (l == 1)
            Y.push_back(alphabet.at(distrib(gen)));
        else
            Y += all_bigrams.at(distrib(gen));
    }

    return Y;
}

std::wstring correlationGen(const std::wstring& input, size_t s0_num, size_t s1_num, size_t l)
{
    std::vector<std::wstring> all_bigrams;
    if (l == 2)
    {
        all_bigrams = generate_all_bigrams_on_alphabet();
    }

    std::wstring Y;
    Y.reserve(input.size());

    size_t s_i = (s0_num + s1_num);
    size_t s_i_plus_1 = (s1_num + s_i);

    for (size_t i = 0; i < (input.size() / l); i++)
    {
        if (l == 1)
            Y.push_back(alphabet.at(s_i % alphabet.size()));
        else
            Y += all_bigrams.at(s_i % all_bigrams.size());

        size_t s_i_min_1 = s_i;
        s_i = s_i_plus_1;
        s_i_plus_1 = s_i + s_i_min_1;
    }

    return Y;
}
