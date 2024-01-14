#include "GeneralInfo.h"

size_t charNumbInAlph(wchar_t ch)
{
    return std::distance(alphabet.begin(), std::find(alphabet.begin(), alphabet.end(), ch));
}
