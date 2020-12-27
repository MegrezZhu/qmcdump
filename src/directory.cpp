#include "directory.h"
using std::string;

bool isSingleFile(const char* path) {
    struct stat s;
    if (stat(path, &s) == 0) {
        if (s.st_mode & S_IFREG) {
            return true;
        }
    }
    return false;
}

bool isDirectory(const char* path) {
    struct stat s;
    if (stat(path, &s) == 0) {
        if (s.st_mode & S_IFDIR) {
            return true;
        }
    }
    return false;
}

void createMultiStageDir(const string &path) {
    string str1, str2;
#if defined(_WIN32)
    int m = 0;
    str1 = path;
    while (m >= 0) {
        m = str1.find('\\');
        if (!str2.empty())
            str2 += '\\';
        str2 += str1.substr(0, m);
        if (access(str2.c_str(), 0) == -1) {
            mkdir(str2.c_str());
        }
        str1 = str1.substr(m + 1, str1.size());
    }
#else
    int m = 0;
    str1 = path[0] == '/' ? path.substr(1, path.size()) : path;
    str2 = path[0] == '/' ? "/" : "";
    while (m >= 0) {
        m = str1.find('/');
        if (str2[str2.size() - 1] != '/')
            str2.push_back('/');
        str2 += str1.substr(0, m);
        if (access(str2.c_str(), 0) == -1) {
            mkdir(str2.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
        }
        str1 = str1.substr(m + 1, str1.size());
    }
#endif
}
