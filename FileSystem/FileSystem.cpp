#include <pch.h>
#include <direct.h>
#include "FileSystem.h"

using namespace salvation::filesystem;
using namespace salvation::memory;

bool salvation::filesystem::FileExists(const char *pFilePath)
{
    FILE* pFile;

    if (fopen_s(&pFile, pFilePath, "r") == 0)
    {
        fclose(pFile);
        return true;
    }
    
    return false;
}

bool salvation::filesystem::DirectoryExists(const char *pDirectoryPath)
{
    struct stat dirStat;
    if (stat(pDirectoryPath, &dirStat) >= 0)
    {
        return true;
    }

    return false;
}

bool salvation::filesystem::CreateDirectory(const char *pDirectoryPath)
{
    bool hasSuccessfullyCreateDirectory = true;

    uintptr_t dirPathStart = reinterpret_cast<uintptr_t>(pDirectoryPath);
    size_t pathLen = strlen(pDirectoryPath);
    str_smart_ptr tmpPath = ThreadHeapAllocator::Allocate(pathLen + 1);
    tmpPath[pathLen] = 0;

    const char* pSubPath = pDirectoryPath;

    do
    {
        pSubPath = strchr(pSubPath + 1, '/');
        if (pSubPath)
        {
            size_t subPathLen = static_cast<size_t>(reinterpret_cast<uintptr_t>(pSubPath) - dirPathStart) + 1;
            memcpy(tmpPath, pDirectoryPath, subPathLen);
            tmpPath[subPathLen] = 0;

            if (!DirectoryExists(tmpPath))
            {
                hasSuccessfullyCreateDirectory &= (_mkdir(tmpPath) == 0);
            }
        }
    } while (pSubPath);

    if (!DirectoryExists(pDirectoryPath))
    {
        hasSuccessfullyCreateDirectory &= (_mkdir(pDirectoryPath) == 0);
    }

    return hasSuccessfullyCreateDirectory;
}

str_smart_ptr&& salvation::filesystem::ExtractDirectoryPath(const char* pFilePath)
{
    const char* pDirectoryEnd = strrchr(pFilePath, '/');
    size_t dirLen = static_cast<size_t>(reinterpret_cast<uintptr_t>(pDirectoryEnd) - reinterpret_cast<uintptr_t>(pFilePath));
    str_smart_ptr dirPath = reinterpret_cast<char*>(ThreadHeapAllocator::Allocate(dirLen + 1));
    dirPath[dirLen] = 0;
    memcpy(dirPath, pFilePath, dirLen);

    return std::move(dirPath);
}
