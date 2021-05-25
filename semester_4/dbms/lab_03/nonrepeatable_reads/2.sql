USE MMORPG
GO
SELECT @@trancount

BEGIN TRANSACTION
    UPDATE Players set Name = 'TestNonrepeatable' WHERE Id = 1;
COMMIT TRANSACTION


UPDATE Players set Name = 'Scarlett' WHERE Id = 1;
