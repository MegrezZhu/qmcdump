#include <iostream>
#include <string>
#include "crypt.h"

using namespace std;

string convertName(const string &filename);

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        cerr << "Usage: qmcdump <input_path> [output_path]" << endl;
        return 1;
    }

    string in = argv[1];
    string out = argc == 3 ? argv[2] : convertName(in);

    bool result = convert(in, out);
    if (!result) {
        return 1;
    } else {
        cout << "dumped to " << out << endl;
    }
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
