#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"
using namespace std;

class Restaurant {
private:
    static int nextRestaurantId;
    int restaurantId;
    string name;
    string location;
    float reviews;
    vector<MenuItem> menu;

public:
    Restaurant(const string& name, const string& location, float reviews = 0.0f) {
        this->name = name;
        this->location = location;
        this->reviews =  reviews;
        this->restaurantId = ++nextRestaurantId;
    }

    ~Restaurant() {
        // Optional: just for clarity or debug
        cout << "Destroying Restaurant: " << name << ", and clearing its menu." << endl;
        menu.clear();
    }

    //Getters and setters
    string getName() const {
        return name;
    }

    void setName(const string &n) {
        name = n;
    }

    string getLocation() const {
        return location;
    }

    void setLocation(const string &loc) {
        location = loc;
    }

    float getReviews() const {
        return reviews;
    }

    void setReviews(const float& r){
        reviews = r;
    }
    
    void addMenuItem(const MenuItem &item) {
        menu.push_back(item);
    }

    const vector<MenuItem>& getMenu() const {
        return menu;
    }
};

int Restaurant::nextRestaurantId = 0;

#endif // RESTAURANT_H