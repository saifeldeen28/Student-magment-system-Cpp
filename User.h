//
// Created by saidn on 5/1/2025.
//

#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

using namespace std;

class User {
private:
    int id;
    string username;
    string password;
    string user_type;
public:
    // Constructor
    User(){}
    User(int id, string username, string password)
        : id(id), username(move(username)), password(move(password)) {}

    // Setters
    void set_id(int newId) { id = newId; }
    void set_username(const string& newUsername) { username = newUsername; }
    void set_password(const string& newPassword) { password = newPassword; }
    void set_user_type(const string& type) { user_type= type; }

    // Getters
    int get_id() const { return id; }
    string get_username() const { return username; }
    string get_password() const { return password; }
    string get_user_type() const { return user_type; }
    virtual void save() = 0;  // Pure virtual function


};

#endif //USER_H