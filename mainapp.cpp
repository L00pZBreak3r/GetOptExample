#include "pch.h"

#include "WordTestCalculate.h"
#include "WordTestChecksum.h"

#include "getopt.h"

using namespace NSWordTests;

static std::wstring aMode;
static std::wstring aWord;
static std::wstring aInputFile;
static bool aCaseInsensitive = false;

static void PrintHelp()
{
  std::wcout <<
    L"--file <filename>: File to read (required)\n"
    L"--mode <modename>: Set mode:\n"
    L"                   words: count words (see --value)\n"
    L"                   checksum: calculate checksum\n"
    L"--value <word>:    Set the word to count\n"
    L"--nocase:          Use case-insensitive word comparison\n"
    L"--help:            Show help\n";
  exit(1);
}

static void ProcessArgs(int argc, _TCHAR* argv[])
{
  const wchar_t* const short_opts = L"m:v:f:nh";
  const option long_opts[] = {
          {L"mode", required_argument, nullptr, L'm'},
          {L"value", required_argument, nullptr, L'v'},
          {L"file", required_argument, nullptr, L'f'},
          {L"nocase", no_argument, nullptr, L'n'},
          {L"help", no_argument, nullptr, L'h'},
          {nullptr, no_argument, nullptr, L'\0'}
  };

  while (true)
  {
    const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

    if (-1 == opt)
      break;

    switch (opt)
    {
    case L'm':
      aMode = std::wstring(optarg);
      break;

    case L'v':
      aWord = std::wstring(optarg);
      break;

    case L'f':
      aInputFile = std::wstring(optarg);
      break;

    case L'n':
      aCaseInsensitive = true;
      break;

    case L'h': // -h or --help
    case L'?': // Unrecognized option
    default:
      PrintHelp();
      break;
    }
  }
}

int _tmain(int argc, _TCHAR* argv[])
{
  _tsetlocale(LC_ALL, _T(".ACP"));

  ProcessArgs(argc, argv);

  if (aInputFile.empty())
  {
    PrintHelp();
  }
  else
    if (aMode.compare(L"checksum") == 0)
    {
      WordTestWordChecksum(std::wcout, aInputFile.c_str());
    }
    else if (aMode.compare(L"words") == 0 || !aWord.empty())
    {
      WordTestWordCalculate(std::wcout, aInputFile.c_str(), aWord.c_str(), aCaseInsensitive);
    }

    return 0;
}
