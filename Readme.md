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
| Single shared restaurant catalog manager | **Singleton** | One source of truth for restaurant data across the app |
| Order/payment status updates reaching interested parties (e.g. notifications) | *Planned: Observer* | Decouples the order/payment flow from anything that reacts to it |

### Core Classes

- **`Restaurant`** — id, name, location, menu (`vector<MenuItem>`)
- **`MenuItem`** — code, name, price
- **`User`** — id, name, address, owns a `Cart`
- **`Cart`** — items in progress, total, clear/is-empty checks
- **`Order`** *(abstract)* — base for order types, exposes `getType()`
- **`RestaurantManager`** *(Singleton)* — add restaurants, search by location
- **`OrderManager`** — orchestrates order creation and lifecycle via `OrderFactory`
- **`PaymentStrategy`** *(abstract)* — `pay()`, implemented by `UPI`, `CreditCard`, `DebitCard`, `NetBanking`
- **`PaymentFactory`** — resolves a payment-type string/enum into the correct `PaymentStrategy`
- **`NotificationService`** — notifies users on order events

### UML Diagram

See [`/docs`](./docs) for the hand-drawn UML diagrams (class relationships, interfaces, and the order/payment flow) this implementation is based on.

## Project Structure

```
ZOMATO-CLONE/
├── factories/        # OrderFactory, PaymentFactory
├── managers/          # RestaurantManager, OrderManager
├── models/            # Restaurant, MenuItem, User, Cart, Order
├── services/          # NotificationService
├── strategies/        # PaymentStrategy and its implementations
├── utils/
├── main.cpp
└── TomatoApp.h
```

## Status

🚧 **Work in progress.** Currently implemented:
- [x] `Restaurant`, `MenuItem` models
- [x] `RestaurantManager` (Singleton) — add + search by location
- [ ] `Cart` — in progress
- [ ] `User` — basic structure in place
- [ ] `Order` hierarchy + `OrderFactory`
- [ ] `PaymentStrategy` hierarchy + `PaymentFactory`
- [ ] `NotificationService`
- [ ] Observer-based decoupling for notifications

## Build

```bash
g++ -std=c++17 main.cpp -o zomato_clone
./zomato_clone
```

## Related

Design pattern fundamentals practiced separately at [DesignPatterns-Practice](https://github.com/Kaushal-15/DesignPatterns-Practice) — this project is where those patterns get applied together in one real system.

## Author

**Kaushal** — built as part of LLD/DSA interview preparation.