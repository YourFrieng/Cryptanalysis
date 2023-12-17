#include "GeneralInfo.h"
#include "AnalyseText.h"
#include <cmath>

enum HYPOTHESIS
{
	H_0,// informative text
	H_1 // random text
};

std::map<std::wstring, size_t> CreateUniformFrequency(const std::wstring& input, size_t l)
{
	std::map<std::wstring, size_t> uniform_frequency;
	switch (l)
	{
	case 1:
		for (const auto& letter_freq_pair : letter_frequency(input))
			uniform_frequency[std::wstring({ letter_freq_pair.first })] = letter_freq_pair.second;
		break;
	case 2:
		uniform_frequency = bigram_count(input);
		break;
	default:
		break;
	}

	return uniform_frequency;
}

/*****************************************************************//**
 * Criterion 2.0
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams0(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l)
{
	auto uniform_frq = CreateUniformFrequency(input, l);

	for (const auto& frq_pair : A_frq)
	{
		auto it_freq = uniform_frq.find(frq_pair.first);
		if (it_freq == uniform_frq.end())
			return H_1;
	}

	return H_0;
}

/*****************************************************************//**
 * Criterion 2.1
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams1(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l, size_t k_f)
{
	auto uniform_frq = CreateUniformFrequency(input, l);

	std::vector<std::wstring> A_af;
	A_af.reserve(A_frq.size());
	for (const auto& frq_pair : A_frq)
	{
		auto it_freq = uniform_frq.find(frq_pair.first);
		if (it_freq != uniform_frq.end())
			A_af.push_back(it_freq->first);
	}

	if (A_af.size() <= k_f)
		return H_1;

	return H_0;
}

/*****************************************************************//**
 * Criterion 2.2
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams2(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l, size_t k_x)
{
	auto uniform_frq = CreateUniformFrequency(input, l);

	for (const auto& frq_pair : A_frq)
	{
		auto it_freq = uniform_frq.find(frq_pair.first);
		if (it_freq != uniform_frq.end())
		{
			if (uniform_frq[it_freq->first] < k_x)
				return H_1;
		}
		else if(k_x != 0)
			return H_1;
	}

	return H_0;
}

/*****************************************************************//**
 * Criterion 2.3
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams3(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l)
{
	auto uniform_frq = CreateUniformFrequency(input, l);

	size_t F_f = 0;
	size_t K_f = 0;
	for (const auto& frq_pair : A_frq)
	{
		auto it_freq = uniform_frq.find(frq_pair.first);
		if (it_freq != uniform_frq.end())
			F_f += it_freq->second;

		K_f += frq_pair.second;
	}

	if (F_f < K_f)
		return H_1;

	return H_0;
}

/*****************************************************************//**
 * Criterion 4.0
 *********************************************************************/
HYPOTHESIS criterionConformityIndex(const std::wstring& input, double I_l/*compliance_index for Language*/, double k_I, size_t l)
{
	auto uniform_frq = CreateUniformFrequency(input, l);
	auto compliance_index = lgram_compliance_index(uniform_frq, input.size(), l);//I_t'

	if (std::fabs(I_l - compliance_index) > k_I)
		return H_1;

	return H_0;
}

/*****************************************************************//**
 * Criterion 5.0
 *********************************************************************/
HYPOTHESIS criterionEmptyBoxes(const std::wstring& input, const std::map<std::wstring, size_t>& lang_rare_lgrams, double k_empt, size_t l)
{
	std::map<std::wstring, size_t> boxes;
	auto uniform_frq = CreateUniformFrequency(input, l);
	for (const auto& lgram : lang_rare_lgrams)
	{
		auto it_frq = uniform_frq.find(lgram.first);
		if (it_frq != uniform_frq.end())
			boxes[lgram.first] = it_frq->second;
		else
			boxes[lgram.first] = 0;
	}

	size_t count_of_empty_boxes = std::count_if(boxes.begin(), boxes.end(), [](const auto& p) { return p.second; });
	if (count_of_empty_boxes <= k_empt)
		return H_1;

	return H_0;
}
