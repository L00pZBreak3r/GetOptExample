#include "pch.h"

#include "WordCalculator.h"
#include "WordUtilities.h"

using namespace NSWordCalculator;
using namespace NSWordCalculatorBasic;

using CWordCalculatorA = CWordCalculator<char>;
using CWordCalculatorW = CWordCalculator<wchar_t>;

namespace NSWordTests
{
#define WORD_DELIMITERS " \t\n\r\"\'`~!@#$%^&*+=|\\/;:.,<>()[]{}?"
  
  void WordTestWordCalculate(std::wostream& aOstrm, const wchar_t* aFileName, const wchar_t* aWord, bool aCaseInsensitive)
  {
    if (aFileName && *aFileName)
    {
      if (!aWord || !*aWord)
      {
        aOstrm << L"Warning: Word to count is empty. All words will be counted.\n";
      }

      const bool aIsUnicode = IsFileUnicodeBom(aFileName);
      if (aIsUnicode)
      {
        CWordCalculatorW aWordCalculator(aOstrm, aCaseInsensitive, aFileName);

        aWordCalculator.SetWord(aWord);
        aWordCalculator.SetDelimiters(_T(WORD_DELIMITERS));
        aWordCalculator.Execute();
      }
      else
      {
        CWordCalculatorA aWordCalculator(aOstrm, aCaseInsensitive, aFileName);
        
        char* aWordA = nullptr;
        int aLen = (aWord) ? (int)wcslen(aWord) : 0;
        if (aLen > 0)
        {
          aLen = WideCharToMultiByte(CP_ACP, 0, aWord, -1, nullptr, 0, nullptr, nullptr);
          if (aLen > 0)
          {
            aWordA = new char[aLen];
            WideCharToMultiByte(CP_ACP, 0, aWord, -1, aWordA, aLen, nullptr, nullptr);
          }
        }

        aWordCalculator.SetWord(aWordA);
        delete[] aWordA;
        
        aWordCalculator.SetDelimiters(WORD_DELIMITERS);
        aWordCalculator.Execute();
      }
    }
    else
    {
      aOstrm << L"Error: Filename is empty\n";
    }
  }
}