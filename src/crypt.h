#include <cstdint>
#include <string>

const int BUFFER_SIZE = 8192;

int encrypt(int offset, char *buf, int len);
char mapL(int v);
bool convert(const std::string &in, const std::string &out);
