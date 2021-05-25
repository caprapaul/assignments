USE MMORPG
GO

BEGIN TRANSACTION
    UPDATE Players set Name = 'TestLock2_2' WHERE Id = 2;
    UPDATE Players set Name = 'TestLock1_2' WHERE Id = 1;
ROLLBACK TRANSACTION
COMMIT TRANSACTION

-- Solution: Choose t1 as the victim by setting the priority of t2 to be higher
SET DEADLOCK_PRIORITY HIGH
BEGIN TRANSACTION
    UPDATE Players set Name = 'TestLock2_2' WHERE Id = 2;
    UPDATE Players set Name = 'TestLock1_2' WHERE Id = 1;
ROLLBACK TRANSACTION
COMMIT TRANSACTION
