CREATE TABLE Customers (
    CustomerID INTEGER PRIMARY KEY AUTOINCREMENT,
    FirstName TEXT NOT NULL,
    LastName TEXT NOT NULL,
    Phone TEXT
);

ALTER TABLE Customers
DROP COLUMN Email;

INSERT INTO Customers (FirstName, LastName, Phone)
VALUES
("John", "Smith", "555-1111"),
("Sarah", "Jones", "555-2222"),
("Mike", "Davis", "555-3333"),
("Emily", "Brown", "555-4444"),
("Alex", "Wilson", "555-5555");

SELECT * FROM Customers
WHERE FirstName = "Sarah" AND LastName = "Jones";

SELECT * FROM Customers
WHERE Phone LIKE "555-%";

CREATE TABLE MenuItems (
    MenuItemID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    Category TEXT NOT NULL CHECK(Category IN ("Entree", "Appetizer", "Dessert", "Side", "Drink")),
    Price DECIMAL(3, 2) NOT NULL
);

INSERT INTO MenuItems (Name, Category, Price)
VALUES
("Cheeseburger", "Entree", 12.99),
("Fries", "Side", 3.99),
("Soda", "Drink", 2.49),
("Chicken Wings", "Appetizer", 9.99),
("Caeser Salad", "Entree", 10.99),
("Milkshake", "Drink", 4.99);

SELECT * FROM MenuItems
WHERE Category = "Drink";

SELECT MIN(Price) AS LowestPrice, Name, Category
FROM MenuItems
GROUP BY Category;

SELECT MAX(Price) AS HighestPrice, Name, Category
FROM MenuItems
GROUP BY Category;

CREATE TABLE Orders (
    OrderID INTEGER PRIMARY KEY AUTOINCREMENT,
    CustomerID INTEGER NOT NULL,
    Date DATE NOT NULL
);

CREATE TABLE OrderItems (
    OrderID INTEGER NOT NULL,
    MenuItemID INTEGER NOT NULL,
    Amount INTEGER NOT NULL
);

INSERT INTO Orders (CustomerID, Date)
VALUES
(1, '06-01-2026'),
(2, '06-02-2026'),
(3, '07-23-2025'),
(1, '03-07-2023');

INSERT INTO OrderItems (OrderID, MenuItemID, Amount)
VALUES
(1, 1, 2),
(1, 2, 1),
(1, 3, 2),
(2, 4, 1),
(2, 6, 1),
(3, 5, 1),
(3, 3, 1);

SELECT * FROM Orders;
SELECT * FROM OrderItems;

SELECT COUNT() AS "John Visit Times" FROM Orders
WHERE CustomerID = 1;

SELECT * FROM OrderItems
INNER JOIN MenuItems ON MenuItems.MenuItemID = OrderItems.MenuItemID
WHERE OrderItems.OrderID = 1;

SELECT * FROM Orders
INNER JOIN Customers ON Orders.CustomerID = Customers.CustomerID
ORDER BY Customers.FirstName;

SELECT SUM(MenuItems.Price) AS Revenue, Orders.Date, Orders.OrderID
FROM Orders
INNER JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
INNER JOIN MenuItems ON OrderItems.MenuItemID = MenuItems.MenuItemID
GROUP BY Orders.Date;

SELECT AVG(MenuItems.Price) AS "Average Cost", Orders.Date, Orders.OrderID
FROM Orders
INNER JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
INNER JOIN MenuItems ON OrderItems.MenuItemID = MenuItems.MenuItemID
GROUP BY Orders.Date;

SELECT MAX(SumPrice) AS Price
FROM (
    SELECT Orders.Date,
           SUM(MenuItems.Price) AS SumPrice
    FROM Orders
    INNER JOIN OrderItems
        ON Orders.OrderID = OrderItems.OrderID
    INNER JOIN MenuItems
        ON OrderItems.MenuItemID = MenuItems.MenuItemID
    GROUP BY Orders.Date
) AS DailyTotals;

SELECT MAX(CustomerOrders) AS "Count of Orders by Customer"
FROM (
    SELECT COUNT(*) AS CustomerOrders
    FROM Orders
    GROUP BY CustomerID
);