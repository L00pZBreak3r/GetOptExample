#pragma once

#include "BasicStream.h"

using namespace NSWordCalculatorBasic;

namespace NSWordChecksum
{

  template <class charT>
  class CWordChecksum : public CBasicStream<charT>
  {
  protected:
    unsigned int mChecksum = 0;

  public:
    CWordChecksum(wostream& aOstrm, const wchar_t* aFileName = nullptr)
      : CBasicStream<charT>(aOstrm, aFileName)
    {

    }
    CWordChecksum(const CWordChecksum&) = delete;
    CWordChecksum(CWordChecksum&&) = delete;

    CWordChecksum& operator=(const CWordChecksum&) = delete;

  protected:

    void DoJob() override
    {
      mChecksum = 0;
      unsigned int n;
      basic_istringstream<charT> aIstrm(this->mText);
      while (aIstrm.read(reinterpret_cast<charT*>(&n), sizeof(n) / sizeof(charT)))
        mChecksum += n;
    }

    void PrintResult(bool aAddNewLine) override
    {
      this->mOstrm << L"Checksum = 0x" << hex << setw(8) << setfill(L'0') << mChecksum;
      if (aAddNewLine)
        this->mOstrm << L'\n';
    }
  };

}