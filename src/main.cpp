#include <iostream>
#include <string>
#include <cstring>
#include "crypt.h"
#include "directory.h"

using std::string;
using std::endl;
using std::cerr;
using std::cout;

string convertName(const string &filename);
int convertSingleFile(const string &in, const string &out);
int convertDirectory(const string &inDir, const string &outDir);


int main(int argc, char **argv) {
    if (argc != 2 && argc != 3 && argc != 4) {
        cerr << "\nUsage\n" << endl;
        cerr << "  qmcdump <input_file_path> [output_file_path]" << endl;
        cerr << "  qmcdump <input_directory> [output_directory]\n" << endl;
        return 1;
    }

    string in = argv[1];

#ifdef WIN32
    if (in[in.size() - 1] == '\\')
        in.pop_back();
#else
    if (in[in.size() - 1] == '/')
        in.pop_back();
#endif

    if (isDirectory(in.c_str())) {
        string out = argc == 3 ? argv[2] : in;
#ifdef WIN32
        if (out[out.size() - 1] == '\\')
            out.pop_back();
#else
        if (out[out.size() - 1] == '/')
            out.pop_back();
#endif
        return convertDirectory(in, out);
    }
    else if (isSingleFile(in.c_str())) {
        string out = argc == 3 ? argv[2] : convertName(in);
        return convertSingleFile(in, out);
    }

    return 0;
}

int convertSingleFile(const string &in, const string &out) {
    bool result = convert(in, out);
    if (!result) {
        return 1;
    } else {
        cout << "Dumped to " << out << endl;
        return 0;
    }
}

int convertDirectory(const string &inDir, const string &outDir) {
    if (!isDirectory(outDir.c_str())) {
        cout << "Output path is not a directory." << endl;
        if (access(outDir.c_str(), 0) == -1) {
            cout << "Create Directory " << outDir << "? [y/N] ";
            char opt = getchar();
            if (opt == 'Y' || opt == 'y') {
                createMultiStageDir(outDir.c_str());
                if (!isDirectory(outDir.c_str())) {
                    cerr << "Failed to create directory." << endl;
                    return 1;
                }
            }
            else {
                cout << "Directory not created. Process end." << endl;
                return 1;
            }
        }
        else {
            return 1;
        }
    }

    int ret = 0;
#ifdef WIN32
    struct _finddata_t fileInfo;
    intptr_t handle = _findfirst((inDir + "\\*").c_str(), &fileInfo);
    if (handle == -1)
        return ret;
    do {
        if (strstr(fileInfo.name, ".qmc0") || strstr(fileInfo.name, ".qmc3") || strstr(fileInfo.name, ".qmcflac")) {
            ret |= convertSingleFile(inDir + '\\' + string(fileInfo.name), outDir + '\\' + convertName(string(fileInfo.name)));
        }
        if (ret)
            return ret;
    } while (!_findnext(handle, &fileInfo));
    _findclose(handle);
#else
    DIR *inPath = opendir(inDir.c_str());
    for (dirent *p = readdir(inPath); p != NULL; p = readdir(inPath)) {
        if (strstr(p->d_name, ".qmc0") || strstr(p->d_name, ".qmc3") || strstr(p->d_name, ".qmcflac")) {
            ret |= convertSingleFile(inDir + '/' + string(p->d_name), outDir + '/' + convertName(string(p->d_name)));
        }
        if (ret)
            return ret;
    }
#endif
    return ret;
}

string convertName(const string &filename) {
    auto pos = filename.rfind('.');
    if (pos == string::npos) {
        cerr << "Warning: no extname." << endl;
        return filename + "_CONVERTED";
    } else {
        auto base = filename.substr(0, pos);
        auto ext = filename.substr(pos + 1);
        if (ext == "qmcflac")
            ext = "flac";
        else if (ext == "qmc0" || ext == "qmc3")
            ext = "mp3";
        else {
            cerr << "Warning: unknown extname (support: qmcflac, qmc0, qmc3)."
                 << endl;
            ext = "mp3";
        }
        return base + '.' + ext;
    }
}
