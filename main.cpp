#include <iostream>
#include "ZomatoApp.h"
using namespace std;

int main() {
    // Create ZomatoApp Object
    ZomatoApp* Zomato = new ZomatoApp();

    // Simulate User 1 (Chennai location)
    User* user1 = new User(101, "Aditya", "Chennai");
    cout << "\nUser: " << user1->getName() << " is active." << endl;

    // User searches for restaurants by location
    vector<Restaurant*> restaurantList = Zomato->searchRestaurants("Chennai");

    if (restaurantList.empty()) {
        cout << "No restaurants found in Chennai!" << endl;
    } else {
        cout << "Found Restaurants in Chennai:" << endl;
        for (auto restaurant : restaurantList) {
            cout << " - " << restaurant->getName() << endl;
        }

        // User selects the first restaurant
        Zomato->selectRestaurant(user1, restaurantList[0]);
        cout << "Selected restaurant: " << restaurantList[0]->getName() << endl;

        // User adds items to the cart
        Zomato->addToCart(user1, "P1"); 
        Zomato->addToCart(user1, "P2"); 

        Zomato->printUserCart(user1);

        // Checkout and Pay using UPI via PaymentFactory
        PaymentStrategy* upiPayment = PaymentFactory::createPaymentStrategy("UPI", "1234567890");
        Order* order1 = Zomato->checkoutNow(user1, "Delivery", upiPayment);
        if (order1) {
            Zomato->payForOrder(user1, order1);
        }
    }
 
    OrderManager::getInstance()->listOrders();

    // Cleanup Code 
    delete Zomato;
    delete user1;

    
    return 0;
}