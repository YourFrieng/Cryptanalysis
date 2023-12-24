#pragma once
#include <string>
#include <map>

enum HYPOTHESIS
{
	H_0,// informative text
	H_1 // random text
};

/*****************************************************************//**
 * Criterion 2.0
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams0(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l);

/*****************************************************************//**
 * Criterion 2.1
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams1(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l, size_t k_f);

/*****************************************************************//**
 * Criterion 2.2
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams2(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l, size_t k_x);

/*****************************************************************//**
 * Criterion 2.3
 *********************************************************************/
HYPOTHESIS criterionFrequentLgrams3(const std::wstring& input, const std::map<std::wstring, size_t>& A_frq, size_t l);

/*****************************************************************//**
 * Criterion 4.0
 *********************************************************************/
HYPOTHESIS criterionConformityIndex(const std::wstring& input, double I_l/*compliance_index for Language*/, double k_I, size_t l);
/*****************************************************************//**
 * Criterion 5.0
 *********************************************************************/
HYPOTHESIS criterionEmptyBoxes(const std::wstring& input, const std::map<std::wstring, size_t>& lang_rare_lgrams, double k_empt, size_t l);

/*****************************************************************//**
 * Structure criterion
 *********************************************************************/
HYPOTHESIS criterionStructure(const std::wstring& input, float comprassion_coef);
