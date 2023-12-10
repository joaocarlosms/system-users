
#ifndef USERS_H
#define USERS_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Users {
private:
    int id;
    string name;
    string email;
    int yo;

public:
    Users();
    Users(int id, string name, string email, int yo);
    Users(const Users& orig);
    void setId(int id);
    int getId() const;
    void setName(string name);
    string getName() const;
    void setEmail(string email);
    string getEmail() const;
    void setYo(int yo);
    int getYo() const;

    void fill_data();
    void print_data();
    void print_summarized() const;
    void copy(const Users& other);
    int isHigherThat(const Users& other);
    bool isEqual(const Users& other);
    string printForSaveFile() const;
    
};

#endif //USERS