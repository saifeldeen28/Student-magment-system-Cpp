//
// Created by saidn on 5/1/2025.
//

#ifndef USER_H
#define USER_H
#include <string>
#include <utility>
using namespace std;
class User{
public:
    int id;
    string username;
    string password;
    User(int id, string username, string password) : id(id), username(move(username)), password(move(password)) {};

};

#endif //USER_H
