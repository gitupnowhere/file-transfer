/// \file control.hpp
///

#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "user.hpp"

int ls(const user_unit * user, char * arg);
int cd(user_unit * user, char * arg);
int mkdir(const user_unit * user, char * arg);
int exit(const user_unit * user);


#endif //CONTROL_HPP
