#include "pch.h"

#include "WordChecksum.h"
#include "WordUtilities.h"

using namespace NSWordChecksum;
using namespace NSWordCalculatorBasic;

using CWordChecksumA = CWordChecksum<char>;
using CWordChecksumW = CWordChecksum<wchar_t>;


namespace NSWordTests
{

  void WordTestWordChecksum(std::wostream& aOstrm, const wchar_t* aFileName)
  {
    if (aFileName && *aFileName)
    {
      const bool aIsUnicode = IsFileUnicodeBom(aFileName);
      if (aIsUnicode)
      {
        CWordChecksumW aWordCalculator(aOstrm, aFileName);

        aWordCalculator.Execute();
      }
      else
      {
        CWordChecksumA aWordCalculator(aOstrm, aFileName);

        aWordCalculator.Execute();
      }
    }
    else
    {
      aOstrm << L"Error: Filename is empty\n";
    }
  }
}