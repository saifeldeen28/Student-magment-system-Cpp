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

public:
    // Constructor
    User(int id, string username, string password)
        : id(id), username(move(username)), password(move(password)) {}

    // Setters
    void setId(int newId) { id = newId; }
    void setUsername(const string& newUsername) { username = newUsername; }
    void setPassword(const string& newPassword) { password = newPassword; }

    // Getters
    int getId() const { return id; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
};

#endif //USER_H
