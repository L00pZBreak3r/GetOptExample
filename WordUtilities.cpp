#include "pch.h"

#include "WordUtilities.h"

namespace NSWordCalculatorBasic
{

  bool IsFileUnicodeBom(std::ifstream& aIfs)
  {
    bool res = false;
    if (aIfs.is_open())
    {
      constexpr unsigned short wBOM = 0xfeffu;
      unsigned short w;
      res = aIfs.read(reinterpret_cast<char*>(&w), sizeof(w)) && (w == wBOM);
      if (!res)
        aIfs.seekg(0);
    }
    return res;
  }

  bool IsFileUnicodeBom(const wchar_t* aFileName)
  {
    std::ifstream ofl(aFileName);
    return IsFileUnicodeBom(ofl);
  }

}