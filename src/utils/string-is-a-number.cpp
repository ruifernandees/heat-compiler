#include <iostream>
#include <string>
#include <climits>
#include <cerrno>

#pragma once

using namespace std;

bool isValidNumber(string num)
{
    char *endptr;
    errno = 0;
    int number = strtol(num.c_str(), &endptr, 10);
    if (*endptr != '\0') {
        return false;
    }
    if (errno == ERANGE || errno == EINVAL || (errno != 0 && number == 0))
        return false;
    if (errno == 0) {
        return true;
    }
}
