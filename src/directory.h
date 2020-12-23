#ifndef QMCDUMP_DIRECTORY_H
#define QMCDUMP_DIRECTORY_H

#include <string>
#ifdef WIN32
#include <io.h>
#include <windows.h>
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif

bool isSingleFile(const char* path);
bool isDirectory(const char* path);
void createMultiStageDir(const std::string &path);

#endif //QMCDUMP_DIRECTORY_H
