USE MMORPG
GO
SELECT @@trancount

BEGIN TRANSACTION
    EXEC insert_player 'TestPhantom', 'testphantom@sometest.com', '2010-07-12'
COMMIT TRANSACTION

DELETE FROM Players WHERE Email = 'testphantom@sometest.com'
