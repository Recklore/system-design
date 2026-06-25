// // OBJECT ORIENTED PROGRAMMING (studied earlier) (revision)
// binary -> assembly -> procedural -> oop


// // Pillars of OOP:

// - Abstraction: the concept of hiding complex and unnecessary internal implementation details
//   while exposing only the essential features to the user

#include <iostream>
using namespace std;

class Car
{
private:
    void startEngine()
    {
        cout << "Engine started internally.\n";
    }

public:
    void drive()
    {
        startEngine();          // Internal implementation hidden
        cout << "Car is moving.\n";
    }
};

// Example:
// int main()
// {
//     Car c;
//     c.drive();       // User only knows "drive()", not how the engine starts
// }


// - Encapsulation: binds data (variables) and methods (functions) into a single unit (class).
//   It also provides data security through access specifiers.

class BankAccount
{
private:
    double balance;

public:
    BankAccount(double b)
    {
        balance = b;
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    void withdraw(double amount)
    {
        if (amount <= balance)
            balance -= amount;
    }

    double getBalance()
    {
        return balance;
    }
};

// Example:
// int main()
// {
//     BankAccount acc(1000);
//     acc.deposit(500);
//     acc.withdraw(200);
//     cout << acc.getBalance();      // 1300
//
//     // acc.balance = 100000;       // Error: balance is private
// }


// - Inheritance: mechanism that allows a new class to acquire the properties
//   and behaviors of an existing class.

class Animal
{
public:
    void eat()
    {
        cout << "Animal is eating.\n";
    }
};

class Dog : public Animal
{
public:
    void bark()
    {
        cout << "Dog is barking.\n";
    }
};

// Example:
// int main()
// {
//     Dog d;
//     d.eat();      // Inherited from Animal
//     d.bark();     // Own function
// }


// - Polymorphism: the ability for different objects to respond to the same
//   method call in their own unique way.

// (A) Static Polymorphism (Compile-time) - Method Overloading

class Calculator
{
public:
    int add(int a, int b)
    {
        return a + b;
    }

    double add(double a, double b)
    {
        return a + b;
    }
};

// Example:
// Calculator c;
// cout << c.add(5, 3);          // Calls int version
// cout << c.add(2.5, 1.8);      // Calls double version


// (B) Dynamic Polymorphism (Run-time) - Method Overriding

class Shape
{
public:
    virtual void draw()
    {
        cout << "Drawing Shape\n";
    }
};

class Circle : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing Circle\n";
    }
};

class Rectangle : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing Rectangle\n";
    }
};

// Example:
// int main()
// {
//     Shape* s;
//
//     Circle c;
//     Rectangle r;
//
//     s = &c;
//     s->draw();     // Drawing Circle
//
//     s = &r;
//     s->draw();     // Drawing Rectangle
// }