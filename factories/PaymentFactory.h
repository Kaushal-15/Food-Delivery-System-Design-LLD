#ifndef PAYMENT_FACTORY_H
#define PAYMENT_FACTORY_H

#include "../strategies/PaymentStrategy.h"
#include "../strategies/UpiPaymentStrategy.h"
#include "../strategies/CreditCardPaymentStrategy.h"
#include <string>

class PaymentFactory {
public:
    static PaymentStrategy* createPaymentStrategy(const string& type, const string& details) {
        if (type == "UPI" || type == "upi") {
            return new UpiPaymentStrategy(details);
        } else if (type == "CreditCard" || type == "Card" || type == "creditcard") {
            return new CreditCardPaymentStrategy(details);
        }
        return nullptr;
    }
};

#endif // PAYMENT_FACTORY_H
