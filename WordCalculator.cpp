#include "pch.h"

#include "WordCalculator.h"

namespace NSWordCalculator
{

  char ToUpperCase(char aChar)
  {
    return (char)(size_t)CharUpperA((LPSTR)aChar);
  }

  wchar_t ToUpperCase(wchar_t aChar)
  {
    return (wchar_t)(size_t)CharUpperW((LPWSTR)aChar);
  }

}