#ifndef CART_H
#define CART_H

#include <vector>
#include <string>
#include <algorithm>
#include "Restaurant.h"
#include "MenuItem.h"

using namespace std;

class Cart {
    private :
        Restaurant* restaurant;
        vector <MenuItem> items;

    public:
        Cart(){
            restaurant =  nullptr;
        }
        
        void addItem(const MenuItem& item){
            if(!restaurant){
                cerr << "Please do Choose a Restaurant before adding an Item to the Cart!" << endl;
                return;
            }
            items.push_back(item);
        }

        double getTotalCost() const {
            double sum = 0;
            for (const auto& it : items){
                sum+=it.getPrice();
            }
            return sum;
        }

        bool isempty(){
            return(!restaurant || items.empty());
        }

        void clear(){
            items.clear();
            restaurant =  nullptr;
        }

        //getter and setters 
        void setRestaurant(Restaurant* r){
            restaurant = r;
        }

        Restaurant* getRestaurant() const {
        return restaurant;
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }
};


#endif