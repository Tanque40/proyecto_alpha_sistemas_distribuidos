#include <string>

class User {
   private:
    static int countUsers;
    int id;
    std::string nombre;
    std::string password;

   public:
    inline User(){};
    User(std::string nombre, std::string password);
    ~User();
    int getId();
    std::string getNombre();
    std::string getPassword();
};