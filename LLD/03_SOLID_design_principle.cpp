// S : Single Responsibility Principle
// a class should only do one thing
// a class should only have one resason to change

// Example: invoice class should not also save to DB or print it
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Invoice
{
private:
    string customerName;
    double amount;

public:
    Invoice(string name, double amt) : customerName(name), amount(amt) {}

    string getCustomerName() const { return customerName; }
    double getAmount() const { return amount; }
};

class InvoicePrinter
{
public:
    void print(const Invoice& invoice)
    {
        cout << "Customer: " << invoice.getCustomerName() << "\n";
        cout << "Amount: $" << invoice.getAmount() << "\n";
    }
};

class InvoiceRepository
{
public:
    void save(const Invoice& invoice)
    {
        cout << "Saved invoice for " << invoice.getCustomerName() << " to database\n";
    }
};

// O : Open-Close Principle
// a class should be open for extension but closed for modification(change in older classes for implementing new features)

class Notification
{
public:
    virtual void send(string message) = 0;
    virtual ~Notification() = default;
};

class EmailNotification : public Notification
{
public:
    void send(string message) override
    {
        cout << "Sending email: " << message << "\n";
    }
};

class SMSNotification : public Notification
{
public:
    void send(string message) override
    {
        cout << "Sending SMS: " << message << "\n";
    }
};

class PushNotification : public Notification
{
public:
    void send(string message) override
    {
        cout << "Sending push notification: " << message << "\n";
    }
};

// L : Liskov Substitution Princple
// a subclass should be substitutable for their base classes
// Signature rule : - have same method signature during overriding (method argument rule)
//                  - have the same (or narrower type)(covariance) return type
//                  - have same or narrower exception thrown if any (exception rule)
// Property rule : - child class should follow the invariant rules of the parent class (class invariant rule)
//                 - constraint set by parent class should be followed by child class (history constraint rule) (immutable properties)
// Method rule : - precondition set on a method can only be weakened by child class and cant be strengthened
//               - postcondition set on a method can only be strenghtened by child class and cant be weakened

class Bird
{
public:
    virtual void fly() { cout << "Bird is flying\n"; }
};

class Sparrow : public Bird
{
public:
    void fly() override { cout << "Sparrow is flying\n"; }
};

// This violates LSP: Penguins are birds, but they cannot fly
// class Penguin : public Bird
// {
//     void fly() override { throw runtime_error("Penguin cannot fly"); }
// };

// Correct design: separate `flyable` capability from Bird itself
class Animal
{
public:
    virtual void sound() { cout << "Animal sound\n"; }
};

class FlyingBird : public Animal
{
public:
    virtual void fly() = 0;
};

class Penguin : public Animal
{
public:
    void sound() override { cout << "Penguin says: squawk\n"; }
};

// I : Interface segregation principle
// many client specific interfaces are better than one general purpose interface
// client should not be forced to implement methods that they wont use

class Workable
{
public:
    virtual void work() = 0;
    virtual ~Workable() = default;
};

class Eatable
{
public:
    virtual void eat() = 0;
    virtual ~Eatable() = default;
};

class Sleepable
{
public:
    virtual void sleep() = 0;
    virtual ~Sleepable() = default;
};

class Employee : public Workable, public Eatable, public Sleepable
{
public:
    void work() override { cout << "Employee is working\n"; }
    void eat() override { cout << "Employee is eating\n"; }
    void sleep() override { cout << "Employee is sleeping\n"; }
};

// D : Dependency inversion principle
// high level modules should not depend on low level modules but rather both should be connected/depend on abstraction
// dependency injection
// open closed principle is solved using dependency inversion principle

class PaymentGateway
{
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentGateway() = default;
};

class StripePayment : public PaymentGateway
{
public:
    void pay(double amount) override
    {
        cout << "Paid " << amount << " using Stripe\n";
    }
};

class RazorpayPayment : public PaymentGateway
{
public:
    void pay(double amount) override
    {
        cout << "Paid " << amount << " using Razorpay\n";
    }
};

class OrderService
{
private:
    PaymentGateway& paymentGateway;

public:
    OrderService(PaymentGateway& gateway) : paymentGateway(gateway) {}

    void checkout(double amount)
    {
        paymentGateway.pay(amount);
    }
};

int main()
{
    Invoice invoice("Aman", 2500.0);
    InvoicePrinter printer;
    InvoiceRepository repository;
    printer.print(invoice);
    repository.save(invoice);

    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    email.send("Welcome to the platform");
    sms.send("OTP: 123456");
    push.send("New feature released");

    Sparrow sparrow;
    sparrow.fly();

    Employee employee;
    employee.work();
    employee.eat();
    employee.sleep();

    StripePayment stripe;
    OrderService order(stripe);
    order.checkout(499.99);

    return 0;
}