# Design Decisions

This document explains *why* each design pattern was chosen for this system — not what the pattern is, but what specific problem in this codebase made it the right fit.

---

## 1. Factory Pattern — Order Creation

**Classes:** `OrderFactory` (interface), `NowOrderFactory`, `ScheduledOrderFactory`

**Problem it solves:**  
The system supports two types of orders — immediate (now) and scheduled. Without a factory, `OrderManager` or `ZomatoApp` would need an `if/else` chain to decide which concrete `Order` subclass to instantiate. Every time a new order type is added, that orchestrator class would need to be modified — violating the Open/Closed Principle.

**Why Factory here:**  
The factory isolates the "which concrete class to build" decision into a dedicated class. `ZomatoApp` just calls `factory->createOrder(...)` — it never needs to know whether the order is a `DeliveryOrder` or `PickupOrder`. Adding a new order type (e.g., `GroupOrder`) means adding one new factory subclass, touching nothing else.

---

## 2. Strategy Pattern — Payment Processing

**Classes:** `PaymentStrategy` (abstract), `UpiPaymentStrategy`, `CreditCardPaymentStrategy`

**Problem it solves:**  
Payment methods (UPI, Credit Card, Debit Card, Net Banking) all perform the same operation — `pay()` — but with different internal logic. Without Strategy, `Order` or `ZomatoApp` would need conditional logic for each payment type, making it harder to add or swap payment methods later.

**Why Strategy here:**  
All payment types implement one interface (`PaymentStrategy`). The `Order` class only ever calls `paymentStrategy->pay()` — it is completely unaware of which concrete payment method is being used. Adding a new payment method requires only a new class implementing `PaymentStrategy`, with zero changes to existing code.

---

## 3. Factory Pattern — Payment Strategy Selection

**Class:** `PaymentFactory`

**Problem it solves:**  
Strategy pattern alone doesn't answer the question: *who decides which concrete `PaymentStrategy` to instantiate at runtime, based on the user's choice?* If `ZomatoApp` or `OrderManager` contained an `if/else` chain (`if type == "UPI" → new UpiPaymentStrategy()`), they would need to be modified every time a new payment method is added — defeating the purpose of Strategy entirely.

**Why Factory here:**  
`PaymentFactory` owns the runtime resolution of a payment type string/enum into the correct concrete strategy object. `ZomatoApp` calls `PaymentFactory::create(type)` and receives a `PaymentStrategy*` — it never sees `UpiPaymentStrategy` or `CreditCardPaymentStrategy` directly. Factory and Strategy must always be paired this way: Strategy defines the *what*, Factory resolves the *which*.

---

## 4. Singleton Pattern — RestaurantManager & OrderManager

**Classes:** `RestaurantManager`, `OrderManager`

**Problem it solves:**  
Both managers maintain shared state — the restaurant catalog and the list of active orders respectively. If multiple instances were allowed, different parts of the codebase could operate on different, inconsistent copies of that data. For example, a restaurant added via one `RestaurantManager` instance might not appear in a search performed through another.

**Why Singleton here:**  
Both managers are stateful, global-scope coordinators — there should be exactly one, for the entire lifetime of the application. Singleton enforces this at the class level rather than relying on convention. Both singletons also expose a `cleanup()` method for explicit destructor control, since their lifetimes span the full program.

---

## 5. Observer Pattern — Order Notifications

**Classes:** `OrderObserver` (interface), `NotificationService`

**Problem it solves:**  
After a successful payment, the user needs to be notified. The naive approach is for `ZomatoApp` or `OrderManager` to directly call `NotificationService::notify(...)`. This tightly couples the order/payment flow to the notification logic — if an email receipt, an SMS, or a push notification needs to be added later, the orchestrator class itself would need to be modified.

**Why Observer here:**  
`ZomatoApp` maintains a list of `OrderObserver*` and calls `notifyObservers(order)` after payment succeeds — it has no knowledge of `NotificationService` directly. `NotificationService` implements `OrderObserver` and registers itself at startup. Adding a new reaction to a placed order (e.g., `AnalyticsService`, `LoyaltyPointsService`) means creating a new class implementing `OrderObserver` and registering it — zero changes to the existing payment or order flow.

---

## Summary

| Pattern | Applied To | Core Reason |
|---|---|---|
| Factory | Order creation | Decouple order type selection from orchestrator |
| Strategy | Payment processing | Interchangeable payment algorithms behind one interface |
| Factory | Payment strategy selection | Resolve runtime payment choice without if/else in orchestrator |
| Singleton | RestaurantManager, OrderManager | Single shared state for catalog and order tracking |
| Observer | Notifications after order placement | Decouple event announcement from event reaction |
