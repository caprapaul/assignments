USE MMORPG
GO

CREATE OR ALTER PROCEDURE insert_player(@name varchar(32), @email VARCHAR(64), @created_at DATE)
AS
    PRINT 'ENTER: insert_player'
    BEGIN TRY
        BEGIN TRANSACTION
            INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES(@name, @email, @created_at);

            PRINT 'COMMIT'
            COMMIT TRANSACTION
    END TRY
    BEGIN CATCH
        PRINT 'ROLLBACK'
        ROLLBACK TRANSACTION
    END CATCH
GO

CREATE OR ALTER PROCEDURE insert_guild(@name varchar(32), @description VARCHAR(128), @created_at DATE)
AS
    PRINT 'ENTER: insert_guild'
    BEGIN TRY
        BEGIN TRANSACTION
            INSERT INTO Guilds([Name],[Description],[CreatedAt]) VALUES(@name, @description, @created_at);

            PRINT 'COMMIT'
            COMMIT TRANSACTION
    END TRY
    BEGIN CATCH
        PRINT 'ROLLBACK'
        ROLLBACK TRANSACTION
    END CATCH
GO

CREATE OR ALTER PROCEDURE insert_player_guild(@guild_name varchar(32), @player_name VARCHAR(32))
AS
    PRINT 'ENTER: insert_player_guild'
    BEGIN TRY
        BEGIN TRANSACTION
            DECLARE @p_id int;
            SELECT @p_id = Id FROM Players WHERE [Name] = @player_name;
            DECLARE @g_id int;
            SELECT @g_id = Id FROM Guilds WHERE [Name] = @guild_name;

            INSERT INTO GuildsPlayers([GuildId], [PlayerId]) VALUES(@p_id, @g_id);

            PRINT 'COMMIT'
            COMMIT TRANSACTION
    END TRY
    BEGIN CATCH
        PRINT 'ROLLBACK'
        ROLLBACK TRANSACTION
    END CATCH
GO

CREATE OR ALTER PROCEDURE insert_rollback
AS
    PRINT 'ENTER: insert_rollback'
    EXEC insert_guild 'Guild1', 'This is guild 1.', '2010-03-12'
    EXEC insert_player 'Player1', 'player1@someplayer.com', '2010-07-12'
    EXEC insert_guild 'Guild1', 'This is guild 1.', '2010-03-12'
    EXEC insert_player_guild 'Player1', 'Guild1'
    PRINT 'EXIT: insert_rollback'
GO

CREATE OR ALTER PROCEDURE insert_commit
AS
    PRINT 'ENTER: insert_commit'
    EXEC insert_player 'Player1', 'player1@someplayer.com', '2010-07-12'
    EXEC insert_guild 'Guild1', 'This is guild 1.', '2010-03-12'
    EXEC insert_player_guild 'Player1', 'Guild1'
    PRINT 'EXIT: insert_commit'
GO

CREATE OR ALTER PROCEDURE reset
AS
    DECLARE @p_id int;
    DECLARE @g_id int;
    SELECT @p_id = Id FROM Players WHERE Name = 'Player1'
    SELECT @g_id = Id FROM Guilds WHERE Name = 'Guild1'

    DELETE FROM Players WHERE Id = @p_id
    DELETE FROM Guilds WHERE Id = @g_id
    DELETE FROM GuildsPlayers WHERE GuildId = @g_id AND PlayerId = @p_id
GO


EXEC insert_commit
EXEC reset
EXEC insert_rollback
EXEC reset

