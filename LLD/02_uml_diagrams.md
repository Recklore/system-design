# UML Diagrams — LLD Notes

## What is a UML Diagram?
- A way to express your application design **diagrammatically** instead of writing long, boring, hard-to-follow paragraphs.
- Shows: what components/objects/entities exist, and how they interact/connect with each other.

## Types of UML Diagrams
UML diagrams are split into two broad categories (14 total: 7 + 7):

| Type | Also called | Describes |
|---|---|---|
| **Structural** | Static diagrams | The *structure* of the application — what components exist and how they're connected |
| **Behavioral** | Dynamic diagrams | How components *interact* — messages sent, methods called between objects |

**Note:** Of the 14 total UML diagrams, only **2 matter for LLD interviews/practical work**:
1. **Class Diagram** (Structural) — used in ~99% of LLD interviews, drawn before writing code
2. **Sequence Diagram** (Behavioral) — not asked everywhere, but makes specific problems much clearer

The other 12 are very use-case specific and rarely needed.

---

## 1. Class Diagram

Shows:
1. The **structure** of a class (name, variables, methods)
2. The **associations/connections** between classes

### Representing a Class
Draw a rectangle split into **3 parts**:

```
┌─────────────────────┐
│      ClassName       │   ← Class name (+ "abstract" if applicable)
├─────────────────────┤
│ - variable: type      │   ← Characteristics / fields
├─────────────────────┤
│ + method(): type      │   ← Behaviors / methods
└─────────────────────┘
```

**Example — `Car` class:**
- Name: `Car`
- Variables: `brand: String`, `model: String`, `engineCC: int`
- Methods: `startEngine()`, `stopEngine()`, `accelerate()`, `brake()` (all `void`)

Format: `variableName : dataType` and `methodName() : returnType`

### Access Modifiers (quick revision)
| Modifier | Within class | Child class | Outside class |
|---|---|---|---|
| Public | ✅ | ✅ | ✅ |
| Protected | ✅ | ✅ | ❌ |
| Private | ✅ | ❌ | ❌ |

**Symbols used in diagrams:**
- `+` → Public
- `#` → Protected
- `-` → Private

Convention (encapsulation): variables → private, methods → public.

### Abstract vs Concrete Class
- If a class has an unimplemented (virtual) method → **Abstract class**.
- Represent by writing `abstract` above the class name.
- Concrete class → nothing extra written.

---

### Class Associations (Connections)

Two broad categories:

#### A. Class-Level Association → **Inheritance**
- An **"is-a" relationship**.
- Example: `Cow is an Animal`, `Tiger is an Animal`, `ManualCar is a Car`.
- **Diagram:** closed/solid arrow pointing from child → parent.

#### B. Object-Level Association → 3 sub-types (all are **"has-a" relationships**)
All three are represented similarly in code (a class holds a reference to another class), but differ conceptually:

| Type | Relationship strength | Meaning | Diagram symbol |
|---|---|---|---|
| **Simple Association** | Weakest | Two objects share a simple link (e.g., `Arjun has-a House` / `Arjun lives in a House`) | Simple open arrow |
| **Aggregation** | Medium | A "container" object holds other objects, but the parts **can exist independently** (e.g., `Room has-a Sofa/Bed/Chair`, but Sofa can exist without Room) | Line with **empty/open diamond** at the container end |
| **Composition** | Strongest | Object made up of parts that **cannot exist independently** (e.g., `Chair has Wheels/Arms/Seat` — a wheel/arm alone doesn't make sense outside the chair) | Line with **filled/solid diamond** at the container end |

**Code representation (for all 3 types of object association):**
```cpp
class A {
    void method1();
};

class B {
    A* a;                  // reference to another class
    B() { a = new A(); }   // initialized in constructor
    void method2();
};
```
To call `method1()` from B: `b->a->method1()` (must go through the reference).

> ⚠️ In real LLD work, **composition is used more often than inheritance**.

> **Subjectivity note:** Whether a relationship is Simple/Aggregation/Composition is often subjective and depends on how you're designing the application (e.g., in a Zomato clone: does `Menu` exist independently of `Restaurant`? Depends on your design choice).

### Practice Exercise (from the lecture)
Draw a class diagram for:
- A `Car` class with 3–4 characteristics and 3–4 behaviors
- Two variations: `ManualCar` (has `changeGear()`) and `ElectricCar` (has `chargeBattery()`)
- Decide: should this be Inheritance or Composition? If Composition, which type?

---

## 2. Sequence Diagram

A **behavioral diagram** — shows how two (or more) objects interact/communicate over time.

### Core Components

1. **Object representation** — just a box with the object name (no internal structure like class diagrams; structure doesn't matter here).

2. **Lifeline** — a dashed vertical line showing how long an object exists in the application.
   - Can start at the beginning of the flow, or mid-way (if the object is created later).

3. **Activation Bar** — a bar on the lifeline showing when the object is **active** (i.e., can send/receive messages). Outside the activation bar, the object is inactive.

4. **Messages** — two main types:
   | Type | Behavior | Arrow style |
   |---|---|---|
   | **Synchronous** | Sender waits for a response before sending next message | Solid line + **closed arrow**; response shown as **dotted line** back |
   | **Asynchronous** | Sender doesn't wait for a response, can send more messages right away | Solid line + **open arrow** |

5. **Create / Destroy Messages**
   - **Create message** → triggers creation of a new object (new lifeline starts).
   - **Destroy message** → ends an existing object's lifeline (marked with an "X" typically).

6. **Lost / Found Messages** (less common, use-case specific)
   - **Lost message**: sent but never reaches the receiver (e.g., receiver's activation bar had already ended). Shown ending in a filled circle.
   - **Found message**: arrives at an object but the sender is unknown/unspecified.

### Other Notations
- **`alt`** — represents if-else logic; shows alternate flows.
- **`opt`** — represents a simple if condition.
- **`loop`** — represents iteration (for/while loop).
> These are used less often since sequence diagrams typically depict the "happy flow."

### How to Draw a Sequence Diagram — Process
1. **Define the use case** (the flow in plain words).
2. **Identify all objects/entities** involved.
3. **Draw**: lifelines for each object → activation bars → messages between them.

### Worked Example: ATM Withdrawal

**Use case:** User goes to ATM, enters account number + amount to withdraw. ATM verifies and dispenses cash.

**Objects identified:** `User`, `ATM`, `Transaction`, `Account`, `CashDispenser`

**Flow:**
1. `User` → `ATM`: `withdraw(amount, accountNumber)` (sync message)
2. `ATM` → creates `Transaction` object (create message)
3. `Transaction` → `Account`: `checkAmount(amount)` (sync message)
4. `Account` → `Transaction`: returns `true` (sufficient funds)
5. `Transaction` object destroyed (destroy message) after returning `true` to `ATM`
6. `ATM` → `CashDispenser`: `withdrawCash()` (sync message)
7. `CashDispenser` → `ATM`: returns amount
8. `ATM` → `User`: hands over cash
9. All lifelines end (flow complete)

> Note: Each **use case** gets its **own sequence diagram** — a full application can have thousands of use cases → thousands of sequence diagrams. You never draw one diagram for the entire app.

---

## Summary Cheat Sheet

| Concept | Symbol |
|---|---|
| Inheritance ("is-a") | Solid line, **closed arrowhead**, pointing to parent |
| Simple Association ("has-a") | Solid line, **open arrowhead** |
| Aggregation ("has-a", detachable parts) | Line with **empty diamond** at container |
| Composition ("has-a", inseparable parts) | Line with **filled diamond** at container |
| Public / Protected / Private | `+` / `#` / `-` |
| Sync message | Solid line, closed arrow + dotted return line |
| Async message | Solid line, open arrow |
| Create message | Arrow to a newly-appearing lifeline |
| Destroy message | Arrow that terminates an existing lifeline |