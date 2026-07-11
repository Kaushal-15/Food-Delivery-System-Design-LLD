# Food Delivery System Design (Zomato/Swiggy Clone) — C++ LLD

A low-level design implementation of a food delivery application, built to practice object-oriented design and design pattern application in C++. This project models the core flow of a Zomato/Swiggy-style platform: searching restaurants, browsing menus, managing a cart, placing orders, and processing payments.

> This is a learning project built as part of LLD interview preparation. The focus is on clean class design and correct application of design patterns, not on production concerns like persistence, networking, or auth.

## Requirements

### Functional
- Search for restaurants based on location
- Browse a restaurant's menu
- Add items to a cart
- Checkout by making a payment
- Notify the user once an order is placed successfully

### Non-Functional
- Scalable and modifiable code — adding new order types, payment methods, or notification channels should not require changes to existing manager/orchestrator classes

## Design Overview

The system is organized around a few key responsibilities, each backed by a deliberate design pattern choice:

| Responsibility | Pattern Used | Why |
|---|---|---|
| Creating the correct `Order` subtype (new vs. scheduled) | **Factory** | Keeps "which concrete class to build" out of `OrderManager` |
| Selecting a payment method at runtime (UPI, Card, etc.) | **Strategy** + **Factory** | One interface for all payment types; a factory resolves the runtime choice (e.g. a string from the UI) into the right concrete strategy |
| Single shared restaurant catalog manager | **Singleton** | One source of truth for restaurant data across the app, with custom cleanups |
| Order/payment status updates reaching interested parties (e.g. notifications) | **Observer** | Decouples the order/payment flow from anything that reacts to it (e.g. `NotificationService` is an `OrderObserver` registered to `ZomatoApp`) |

### Core Classes

- **`Restaurant`** — id, name, location, menu (`vector<MenuItem>`)
- **`MenuItem`** — code, name, price
- **`User`** — id, name, address, owns a `Cart`
- **`Cart`** — items in progress, total, clear/isEmpty checks
- **`Order`** *(abstract)* — base for order types, exposes `getType()`
- **`RestaurantManager`** *(Singleton)* — add restaurants, search by location, destructor cleanup
- **`OrderManager`** *(Singleton)* — orchestrates order creation and lifecycle, destructor cleanup
- **`PaymentStrategy`** *(abstract)* — `pay()`, implemented by `UPI`, `CreditCard`
- **`PaymentFactory`** — resolves a payment-type string/enum into the correct `PaymentStrategy`
- **`NotificationService`** — implements `OrderObserver` to notify users on order placement events

### UML Diagram

See [`/docs`](./docs) for the hand-drawn UML diagrams (class relationships, interfaces, and the order/payment flow) this implementation is based on.

## Project Structure

```
ZOMATO-CLONE/
├── factories/        # OrderFactory, NowOrderFactory, ScheduledOrderFactory, PaymentFactory
├── managers/         # RestaurantManager, OrderManager
├── models/           # Restaurant, MenuItem, User, Cart, Order, DeliveryOrder, PickupOrder
├── services/         # OrderObserver, NotificationService
├── strategies/       # PaymentStrategy, UpiPaymentStrategy, CreditCardPaymentStrategy
├── utils/            # TimeUtils
├── main.cpp
└── ZomatoApp.h
```

## Status

✅ **Fully Implemented and Verified.**
- [x] `Restaurant`, `MenuItem` models
- [x] `RestaurantManager` (Singleton) — add, search, and dynamic cleanup
- [x] `Cart` — fully implemented, supporting adding items, total cost calculation, and clearing
- [x] `User` — profiles with address and cart bindings
- [x] `Order` hierarchy (`DeliveryOrder` and `PickupOrder`) + polymorphic checkout factories (`NowOrderFactory`, `ScheduledOrderFactory`)
- [x] `PaymentStrategy` hierarchy (`UpiPaymentStrategy`, `CreditCardPaymentStrategy`) + dynamic `PaymentFactory` resolver
- [x] `NotificationService` decoupled using the **Observer Pattern** (`OrderObserver` interface) for event notification
- [x] Leak-free memory management with explicit destructor cleanups of singletons, observers, and strategies

## Build

```bash
g++ -std=c++17 main.cpp -o zomato_clone
./zomato_clone
```

## Related

Design pattern fundamentals practiced separately at [DesignPatterns-Practice](https://github.com/Kaushal-15/DesignPatterns-Practice) — this project is where those patterns get applied together in one real system.

## Author

**Kaushal** — built as part of LLD/DSA interview preparation.