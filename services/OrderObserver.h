#ifndef ORDER_OBSERVER_H
#define ORDER_OBSERVER_H

#include "../models/Order.h"

class OrderObserver {
public:
    virtual void onOrderPlaced(Order* order) = 0;
    virtual ~OrderObserver() {}
};

#endif // ORDER_OBSERVER_H
