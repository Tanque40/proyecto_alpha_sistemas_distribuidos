#include "User.h"

int User::countUsers = 0;

User::User(std::string nombre, std::string password)
    : nombre(nombre), password(password) {
    countUsers++;
    id = countUsers;
}

User::~User() {
    id = 0;
    nombre = "";
    password = "";
}

int User::getId() {
    return id;
}

std::string User::getNombre() {
    return nombre;
}

std::string User::getPassword() {
    return password;
}