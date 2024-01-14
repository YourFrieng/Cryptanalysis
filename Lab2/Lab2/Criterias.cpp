#include "Criterias.h"
#include "GeneralInfo.h"
#include "AnalyseText.h"
#include <cmath>
#define LZMA_API_STATIC
#include <lzma.h>

/*****************************************************************//**
 * Criterion 2.0
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams0(const std::wstring& input, const std::vector<std::wstring>& A_frq, size_t l)
{
	auto uniform_frq = CreateUniformFrequency(input, l);

	for (const auto& frq_pair : A_frq)
	{
		auto it_freq = uniform_frq.find(frq_pair);
		if (it_freq == uniform_frq.end())
			return H_1;
	}

	return H_0;
}

/*****************************************************************//**
 * Criterion 2.1
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams1(const std::wstring& input, const std::vector<std::wstring>& A_frq, size_t l, size_t k_f)
{
	auto uniform_frq = CreateUniformFrequency(input, l);

	std::vector<std::wstring> A_af;
	A_af.reserve(A_frq.size());
	for (const auto& frq_pair : A_frq)
	{
		auto it_freq = uniform_frq.find(frq_pair);
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
HYPOTHESIS criterionEmptyBoxes(const std::wstring& input, const std::vector<std::wstring>& lang_rare_lgrams, size_t k_empt, size_t l)
{
	std::map<std::wstring, size_t> boxes;
	auto uniform_frq = CreateUniformFrequency(input, l);
	for (const auto& lgram : lang_rare_lgrams)
	{
		auto it_frq = uniform_frq.find(lgram);
		if (it_frq != uniform_frq.end())
			boxes[lgram] = it_frq->second;
		else
			boxes[lgram] = 0;
	}

	size_t count_of_empty_boxes = std::count_if(boxes.begin(), boxes.end(), [](const auto& p) { return p.second; });
	if (count_of_empty_boxes <= k_empt)
		return H_1;

	return H_0;
}

/*****************************************************************//**
 * Structure criterion 
 *********************************************************************/
std::wstring compressInput(const std::wstring& input)
{
	size_t inputSize = input.size();
	size_t bufferSize = input.size();
	size_t compressedSize = 0;
	lzma_ret ret;


	// Creating struct for compression
	lzma_stream strm = LZMA_STREAM_INIT;

	ret = lzma_easy_encoder(&strm, LZMA_PRESET_DEFAULT, LZMA_CHECK_CRC64);
	if (ret != LZMA_OK)
		throw "Error in encoder initializing";

	// Setting input buffer
	strm.next_in = reinterpret_cast<const uint8_t*>(input.c_str());
	strm.avail_in = inputSize;

	// Initialize buffer where will be compressed data
	std::vector<uint8_t> outputBuffer(bufferSize);
	strm.next_out = outputBuffer.data();
	strm.avail_out = bufferSize;

	// Data comprassion
	ret = lzma_code(&strm, LZMA_FINISH);
	if ((ret != LZMA_STREAM_END) && (ret != LZMA_OK))
	{
		lzma_end(&strm);
		throw "Error in comprassion";
	}

	// Get size of compressed data
	compressedSize = strm.total_out;

	std::wstring compressedData(reinterpret_cast<wchar_t*>(outputBuffer.data()), strm.total_out);

	//End of work
	lzma_end(&strm);

	return compressedData;
}

/**
 * Compress text and calculate "compression coefficient"(compressed_size / original_size).
 * Check if calculated "compression coefficient" smaller then maximal - 'comprassion_coef'
 * 
 * @param input - text which we want to check
 * @param comprassion_coef - the ratio of the compressed size to the original size (compressed_size / original_size)
 * @return is text informative
 */
HYPOTHESIS criterionStructure(const std::wstring& input, float comprassion_coef)
{
	auto compressed_input = compressInput(input);
	float calc_comp_coef = static_cast<float>(compressed_input.size()) / static_cast<float>(input.size());
	if (calc_comp_coef < comprassion_coef)
		return H_0;

	return H_1;
}
