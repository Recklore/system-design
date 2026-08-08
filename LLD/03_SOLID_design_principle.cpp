// S : Single Responsibility Principle
// a class should only do one thing
// a class should only have one resason to change

// O : Open-Close Principle
// a class should be open for extension but closed for modification(change in older classes for implementing new features)

// L : Liskov Substitution Princple
// a subclass should be substitutable for their base classes
// Signature rule : - have same method signature during overriding (method argument rule)
//                  - have the same (or narrower type)(covariance) return type
//                  - have same or narrower exception thrown if any (exception rule)
// Property rule : - child class should follow the invariant rules of the parent class (class invariant rule)
//                 - constraint set by parent class should be followed by child class (history constraint rule) (immutable properties)
// Method rule : - precondition set on a method can only be weakened by child class and cant be strengthened
//               - postcondition set on a method can only be strenghtened by child class and cant be weakened

// I : Interface segregation principle
// many client specific interfaces are better than one general purpose interface
// client should not be forced to implement methods that they wont use

// D : Dependency inversion principle
// high level modules should not depend on low level modules but rather both should be connected/depend on abstraciton
// dependency injection
// open closed principle is solved using dependency inversion principle