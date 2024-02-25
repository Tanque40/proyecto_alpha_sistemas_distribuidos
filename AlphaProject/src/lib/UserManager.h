#include "User.h"

class UserManager {
   private:
    int sizeUsers;
    int currentPosition;
    User* users;

   public:
    UserManager();
    ~UserManager();
    void newUser(std::string nombre, std::string password);
    User* getUser(int id);

   private:
    void growUsers();
};