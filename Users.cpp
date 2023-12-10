#include "Users.h"

Users::Users()
{
    this->id = 0;
    this->name = " ";
    this->email = " ";
    this->yo = 0;
}

Users::Users(int id, string name, string email, int yo)
{
    this->id = id;
    this->name = name;
    this->email = email;
    this->yo = yo;
}

Users::Users(const Users& orig)
{
    this->id = orig.getId();
    this->name = orig.getName();
    this->email = orig.getEmail();
    this->yo = orig.getYo();
}

void Users::setId(int id)
{
    this->id = id;
}

int Users::getId() const 
{
    return id;
}

void Users::setName(string name)
{
    this->name = name;
}

string Users::getName() const 
{
    return name;
}

void Users::setEmail(string email)
{
    this->email = email;
}

string Users::getEmail() const
{
    return email;
}

void Users::setYo(int yo)
{
this->yo = yo;
}

int Users::getYo() const 
{
    return yo;
}

void Users::fill_data()
{
    cout << "----------FILL DATA--------\n";
    cout << "ID: ";
    cin >> this->id;
    cout << "NAME: ";
    cin.ignore();
    getline(cin, this->name);
    cout << "EMAIL: ";
    getline(cin, this->email);
    cout << "YEARS OLD: ";
    cin >> this->yo;
}

void Users::print_data()
{
    cout << "-------DATA OF USER-------\n";
    cout << "ID: " + id;
    cout << "NAME: " + name;
    cout << "EMAIL:" + email;
    cout << "YO: " + yo; 
}

void Users::print_summarized() const 
{
    cout << left << setw(20) << "ID" << setw(20) << "name" << setw(20) << "email" << "yo\n";
    cout << left << setw(20) << id << setw(20) << name << setw(20) << email << yo << "\n";
}

void Users::copy(const Users& other)
{
    id = other.getId();
    name = other.getName();
    email = other.getEmail();
    yo = other.getYo();
}

int Users::isHigherThat(const Users& other)
{
    if(other.getId() > id)
        return 1;
    else if(other.getId() < id)
        return -1;
    else 
        return 0;
}

bool Users::isEqual(const Users& other)
{
    if(id != other.getId())
        return false;
    if(name != other.getName())
        return false;
    if(email != other.getEmail())
        return false;
    if(yo != other.getYo())
        return false;
    
    return true;
}

string Users::printForSaveFile() const
{
    string text;
    text = to_string(id) + " " +
    name + " " +
    email + " " +
    to_string(yo);

    return text;
}