#pragma once

#include "BasicStream.h"

#include <string>

using namespace NSWordCalculatorBasic;

namespace NSWordCalculator
{

  char ToUpperCase(char aChar);
  wchar_t ToUpperCase(wchar_t aChar);

  template <class charT>
  class CWordCalculator : public CBasicStream<charT>
  {
  protected:
    basic_string<charT> mWord;
    basic_string<charT> mDelimiters;
    size_t mWordCount = 0;
    bool mCaseInsensitive;

  public:
    CWordCalculator(wostream& aOstrm, bool aCaseInsensitive = false, const wchar_t* aFileName = nullptr)
      : CBasicStream<charT>(aOstrm, aFileName), mCaseInsensitive(aCaseInsensitive)
    {

    }
    CWordCalculator(const CWordCalculator&) = delete;
    CWordCalculator(CWordCalculator&&) = delete;

    CWordCalculator& operator=(const CWordCalculator&) = delete;

    void SetWord(const charT* aWord)
    {
      if (aWord)
        mWord = aWord;
      else
        mWord.clear();
    }

    void SetDelimiters(const charT* aDelimiters)
    {
      if (aDelimiters)
        mDelimiters = aDelimiters;
      else
        mDelimiters.clear();
    }

    void SetCaseInsensitivity(bool aCaseInsensitive)
    {
      mCaseInsensitive = aCaseInsensitive;
    }

  protected:
        
    static bool CaseInsensitiveCompare(const basic_string<charT>& str1, const basic_string<charT>& str2)
    {
      return ((str1.size() == str2.size()) && equal(str1.begin(), str1.end(), str2.begin(), [](const charT& c1, const charT& c2)
        {
          return (c1 == c2 || ToUpperCase(c1) == ToUpperCase(c2));
        }
      ));
    }

    void DoJob() override
    {
      mWordCount = 0;

      size_t start = this->mText.find_first_not_of(mDelimiters), end = 0;

      while ((end = this->mText.find_first_of(mDelimiters, start)) != basic_string<charT>::npos)
      {
        basic_string<charT> aWord(this->mText.substr(start, end - start));
        if (mWord.empty())
        {
          mWordCount++;
        }
        else
          if (mCaseInsensitive)
          {
            if (CaseInsensitiveCompare(mWord, aWord))
              mWordCount++;
          }
          else
          {
            if (mWord.compare(aWord) == 0)
              mWordCount++;
          }
        start = this->mText.find_first_not_of(mDelimiters, end);
      }
      if (start != basic_string<charT>::npos)
      {
        basic_string<charT> aWord(this->mText.substr(start));
        if (mWord.empty())
        {
          mWordCount++;
        }
        else
          if (mCaseInsensitive)
          {
            if (CaseInsensitiveCompare(mWord, aWord))
              mWordCount++;
          }
          else
          {
            if (mWord.compare(aWord) == 0)
              mWordCount++;
          }
      }

    }

    void PrintResult(bool aAddNewLine) override
    {
      this->mOstrm << L"Count of \"" << mWord.c_str() << L"\" = " << dec << mWordCount;
      if (aAddNewLine)
        this->mOstrm << L'\n';
    }
  };

}