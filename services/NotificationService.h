#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <iostream>
#include "OrderObserver.h"
using namespace std;

class NotificationService : public OrderObserver {
public:
    void onOrderPlaced(Order* order) override {
        cout << "\nNotification: New " << order->getType() << " order placed!" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Order ID: " << order->getOrderId() << endl;
        cout << "Customer: " << order->getUser()->getName() << endl;
        cout << "Restaurant: " << order->getRestaurant()->getName() << endl;
        cout << "Items Ordered:\n";

        const vector<MenuItem>& items = order->getItems();
        for (const auto& item : items) {
            cout << "   - " << item.getName() << " (₹" << item.getPrice() << ")\n";
        }

        cout << "Total: ₹" << order->getTotal() << endl;
        cout << "Scheduled For: " << order->getScheduled() << endl;
        cout << "Payment: Done" << endl;
        cout << "---------------------------------------------" << endl;
    }
};

#endif // NOTIFICATION_SERVICE_H