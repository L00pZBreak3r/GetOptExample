#pragma once

#include "WordUtilities.h"

using namespace std;

namespace NSWordCalculatorBasic
{
  template <class charT>
  class CBasicStream
  {
  protected:
    wostream& mOstrm;
    basic_string<charT> mText;

  public:
    CBasicStream(wostream& aOstrm, const wchar_t* aFileName = nullptr)
      : mOstrm(aOstrm)
    {
      if (aFileName && *aFileName)
      {
        ifstream aIfs(aFileName, ios::in | ios::binary);
        if (aIfs.is_open())
        {
          const streamoff aOff = (IsFileUnicodeBom(aIfs)) ? 2 : 0;

          aIfs.seekg(0, ios::end);
          const size_t aSize = (size_t)aIfs.tellg() - aOff;
          aIfs.seekg(aOff, ios::beg);
          mText.resize(aSize / sizeof(charT) + 1);
          aIfs.read((char*)&mText[0], aSize);
        }
      }
    }
    CBasicStream(const CBasicStream&) = delete;
    CBasicStream(CBasicStream&&) = delete;

    CBasicStream& operator=(const CBasicStream&) = delete;

    virtual ~CBasicStream()
    {

    }

    void Execute(bool aAddNewLine = true)
    {
      DoJob();
      PrintResult(aAddNewLine);
    }

  protected:
    virtual void DoJob() = 0;
    virtual void PrintResult(bool aAddNewLine) = 0;
  };

}