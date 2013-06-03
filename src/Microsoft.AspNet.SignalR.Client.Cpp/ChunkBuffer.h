#pragma once

#include <http_client.h>
#include "StringHelper.h"

using namespace std;
using namespace utility;

class ChunkBuffer
{
public:
    ChunkBuffer(void);
    ~ChunkBuffer(void);

    bool HasChuncks();
    void Add(char buffer[]);
    string_t ReadLine();

private:
    unsigned int mOffset;
    string_t mBuffer;
    string_t mLineBuilder;
};