#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include <vector>
#include <string>
#include <algorithm>
#include "../models/Restaurant.h"
using namespace std;

class RestaurantManager {
private:
    vector<Restaurant*> restaurants;
    static RestaurantManager* instance;

    RestaurantManager(){

    }

    ~RestaurantManager() {
        for (auto r : restaurants) {
            delete r;
        }
        restaurants.clear();
    }

public:
    static RestaurantManager* getInstance(){
        if(!instance){
            instance = new RestaurantManager();
        }
        return instance;
    }

    static void cleanup() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }

    void addRestaurant(Restaurant* r){
        restaurants.push_back(r);
    }
    vector<Restaurant*> searchByLocation(string loc){
        vector<Restaurant*> result;
        transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
        for(auto r : restaurants){
            string rl = r->getLocation();
            transform(rl.begin(),rl.end(),rl.begin(), ::tolower);
            if(rl == loc ){
                result.push_back(r);
            }
        }
        return result;
    }

};

RestaurantManager* RestaurantManager::instance =  nullptr;

#endif