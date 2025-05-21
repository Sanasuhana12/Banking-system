#ifndef FILEIO_H
#define FILEIO_H

#include "account.h"

class FileIO {
public:
    static void save(Account* head, const std::string& filename);
    static Account* load(const std::string& filename);
};

#endif