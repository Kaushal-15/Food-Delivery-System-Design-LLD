#ifndef USER_H
#define USER_H

#include <string>
#include "Cart.h"
using namespace std;

class User{
    private:
    int UserId;
    string name;
    string address;
    Cart* cart;

    public:
    User(int UserId,const string& name,const string& address){
        this->UserId =  UserId;
        this->name =  name;
        this->address =  address;
        cart = new Cart();
    }

    ~User(){
        delete cart;
    }

    string getName () const {
        return name;
    }

    string setName(const string& n){
        name =  n ;
    }
    
     string getAddress() const {
        return address;
    }

    void setAddress(const string &a) {
        address = a;
    }

    Cart* getCart() const {
        return cart;
    }
};

#endif
