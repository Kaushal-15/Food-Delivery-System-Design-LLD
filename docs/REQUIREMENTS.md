# Requirements — Food Delivery System (Zomato/Swiggy Clone)

---

## Functional Requirements

These are the core capabilities the system must support.

### User
- A user can register with a name, address, and unique ID.
- A user owns exactly one cart at any point in time.

### Restaurant & Menu
- The system maintains a catalog of restaurants, each with a name and location.
- Each restaurant has a menu consisting of items with a code, name, and price.
- A user can search for restaurants by location (case-insensitive).
- A user can browse the menu of any restaurant.

### Cart
- A user can select a restaurant and add menu items to their cart.
- The cart tracks all added items and calculates the running total cost.
- A user can clear their cart.
- The cart is tied to one restaurant at a time.

### Order
- A user can place an immediate order (delivered or picked up now).
- A user can place a scheduled order (delivered or picked up at a specified time).
- An order records the user, restaurant, items ordered, total cost, and payment method.
- An order supports two fulfillment types: Delivery and Pickup.

### Payment
- A user can pay for an order using one of the following methods: UPI, Credit Card, Debit Card, Net Banking.
- The payment method is selected at checkout time.
- On successful payment, the user's cart is cleared.

### Notifications
- The user is notified when an order is placed successfully after payment.

---

## Non-Functional Requirements

These define the quality and design constraints of the system.

### Extensibility
- Adding a new order type (e.g., GroupOrder, BulkOrder) must not require changes to existing manager or orchestrator classes.
- Adding a new payment method (e.g., Wallet, Gift Card) must not require changes to existing order or orchestrator classes.
- Adding a new notification channel (e.g., SMS, Email, Push) must not require changes to the payment or order flow.

### Maintainability
- Each class must have a single, clearly defined responsibility (Single Responsibility Principle).
- Orchestrator classes (ZomatoApp, OrderManager) must not contain conditional logic for selecting concrete implementations — that belongs in Factory classes.

### Memory Safety
- All dynamically allocated objects must be explicitly freed.
- Singleton instances must expose a cleanup method for controlled destruction.
- Observers registered at startup must be deleted when the application shuts down.

### Correctness
- The restaurant catalog must be a single shared instance across the entire application — no duplicate or inconsistent copies.
- The order list must be maintained by a single shared OrderManager instance.

---

## Out of Scope (for this LLD exercise)

- User authentication and authorization
- Persistent storage (database, file system)
- Network communication or REST APIs
- Real payment gateway integration
- Real-time delivery tracking
- Concurrent / multi-threaded order processing
