USE coffee_shops
GO

BEGIN TRANSACTION
    UPDATE CoffeeProducts set Name = 'TestDirty' WHERE Id = 1;
    WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION
