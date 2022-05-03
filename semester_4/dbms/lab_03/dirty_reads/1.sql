USE coffee_shops
GO

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRANSACTION
    SELECT * FROM CoffeeProducts
    WAITFOR DELAY '00:00:20'
    SELECT * FROM CoffeeProducts
COMMIT TRANSACTION

-- Solution: Set the isolation level to READ COMMITTED
SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRANSACTION
    SELECT * FROM CoffeeProducts
    WAITFOR DELAY '00:00:20'
    SELECT * FROM CoffeeProducts
COMMIT TRANSACTION