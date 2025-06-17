#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class LoginManager
{
public:
    bool login();
    void registerUser();
    bool checkCredentials(const string& u, const string& p);
};

#endif
