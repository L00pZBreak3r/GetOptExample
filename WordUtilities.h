#pragma once


namespace NSWordCalculatorBasic
{
  bool IsFileUnicodeBom(std::ifstream& aIfs);
  bool IsFileUnicodeBom(const wchar_t* aFileName);

}