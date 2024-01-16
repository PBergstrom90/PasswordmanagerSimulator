#ifndef __USER_H
#define __USER_H

class User {

    public:
        User(std::string username, std::string password);
        std::string getUsername();
        std::string getPassword();
        void setUsername(std::string username);
        void setPassword(std::string password);
        void printUser();
    private:
        std::string username;
        std::string password;
};

#endif // __USER_H