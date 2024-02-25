#include "UserManager.h"

UserManager::UserManager() {
    sizeUsers = 2;
    currentPosition = 0;
    users = new User[sizeUsers];
}

UserManager::~UserManager() {
    sizeUsers = 0;
    currentPosition = 0;
    users = 0;
}

void UserManager::newUser(std::string nombre, std::string password) {
    if (currentPosition + 1 >= sizeUsers)
        growUsers();

    User user = User(nombre, password);
    users[currentPosition] = user;
    currentPosition++;
}

User* UserManager::getUser(int id) {
    for (size_t i = 0; i < currentPosition; i++) {
        if (users[i].getId() == id) {
            return &users[i];
        }
    }

    return nullptr;
}

void UserManager::growUsers() {
    sizeUsers *= 2;
    User* tempUsers = new User[sizeUsers];

    for (size_t i = 0; i < currentPosition; i++) {
        tempUsers[i] = users[i];
    }

    users = tempUsers;
}
