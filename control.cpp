/// \file control.cpp
///

#include "control.hpp"

#include <stdio.h>
#include <unistd.h>

int ls(const user_unit * user, char * arg) {

}

int cd(user_unit * user, char * arg) {

}

int mkdir(const user_unit * user, char * arg) {

}

int exit(const user_unit * user) {
    int flg;

    flg = close(user->sock);
    if (flg != 0)
        return flg;

    flg = close(user->data_sock);
    if (flg != 0)
        return flg;

    for (auto & it : user->fps) {
        flg = fclose(it.second);
        if (flg != 0)
            return flg;
    }
    return 0;
}
