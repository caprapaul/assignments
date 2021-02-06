USE MMORPG;
GO
SET DATEFORMAT dmy;
GO;

ALTER TABLE GuildsPlayers
DROP CONSTRAINT [PK__GuildsPl__3214EC07526B2A09];

ALTER TABLE GuildsPlayers
ALTER COLUMN GuildId int NOT NULL;

ALTER TABLE GuildsPlayers
ALTER COLUMN PlayerId int NOT NULL;

ALTER TABLE GuildsPlayers
ADD CONSTRAINT [PK__GuildsPlayers] PRIMARY KEY(GuildId, PlayerId);

GO

--

INSERT INTO Tables VALUES ('Players'), ('Characters'), ('GuildsPlayers');
INSERT INTO Views VALUES ('ViewPlayers'), ('ViewCharacters'), ('ViewGuildsPlayers');
INSERT INTO Tests VALUES ('insert_rows'), ('delete_rows'), ('select_view');
INSERT INTO TestViews VALUES (1, 1), (2, 2), (3, 3);
INSERT INTO TestTables VALUES 
	(1, 1, 10, 0), (2, 1, 10, 0), (3, 1, 10, 0),
	(1, 2, 10, 0), (2, 2, 10, 0), (3, 2, 10, 0),
	(1, 3, 10, 0), (2, 3, 10, 0), (3, 3, 10, 0);

GO

SELECT * FROM Tests;

--

CREATE VIEW ViewPlayers AS
	SELECT * FROM Players
GO

CREATE VIEW ViewCharacters AS
	SELECT * FROM Characters
GO

CREATE VIEW ViewGuildsPlayers AS
	SELECT Guilds.[Name] as [GuildName], Players.[Name] as [PlayerName]
	FROM Guilds
	INNER JOIN GuildsPlayers
	ON Guilds.[Id] = GuildsPlayers.[GuildId]
	INNER JOIN Players
	ON Players.[Id] = GuildsPlayers.[PlayerId]
	GROUP BY Guilds.[Name], Players.[Name];
GO

CREATE OR ALTER PROCEDURE insert_rows
@no_of_rows int, 
@table_name varchar(50)
AS
BEGIN
	IF @no_of_rows < 1
	BEGIN
		RAISERROR('Invalid number of rows', 16, 1);
		RETURN;
	END

	DECLARE @i int;

	DECLARE @p_id int;
	DECLARE @p_name varchar(64);
	DECLARE @g_id int;
	DECLARE @g_name varchar(32);

	SET @i = 0;
    WHILE @i < @no_of_rows
	BEGIN
		IF @table_name = 'Players'
        BEGIN
			SET @p_name = CONCAT('Player', @i);
            INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES(@p_name, CONCAT('player', @i, '@something.edu'), '12/11/2020');
        END

		IF @table_name = 'Characters'
        BEGIN
			

			SET @p_name = CONCAT('Player_C', @i);

			INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES(@p_name, CONCAT('player', @i, '@something.edu'), '12/11/2020');
			SELECT @p_id = Id FROM Players WHERE [Name] = @p_name;
            INSERT INTO Characters([PlayerId],[AttributesId],[Name],[Lvl],[Xp],[Online]) VALUES(@p_id, 4, CONCAT('Character', @i), 24, 783, 0);
        END

		IF @table_name = 'GuildsPlayers'
        BEGIN
			

			SET @p_name = CONCAT('Player_GP', @i);
			SET @g_name = CONCAT('Guild_GP', @i);

			INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES(@p_name, CONCAT('player_g', @i, '@something.edu'), '12/11/2020');
            INSERT INTO Guilds([Name],[Description],[CreatedAt]) VALUES(@g_name, 'Join us!', '06/06/2019');

			SELECT @p_id = Id FROM Players WHERE [Name] = @p_name;
			SELECT @g_id = Id FROM Guilds WHERE [Name] = @g_name;

			INSERT INTO GuildsPlayers([GuildId], [PlayerId]) VALUES(@p_id, @g_id);
        END
	END
END
GO

CREATE OR ALTER PROCEDURE delete_rows 
@no_of_rows int, 
@table_name varchar(50) 
AS
BEGIN
	IF @no_of_rows < 1
	BEGIN
		RAISERROR('Invalid number of rows', 16, 1);
		RETURN;
	END
        
	DECLARE @first_id int;
	IF @table_name = 'Players'
    BEGIN
		SET @first_id = (SELECT MAX(Id) FROM Players) - @no_of_rows;

		DELETE FROM GuildsPlayers WHERE PlayerId > @first_id;
		DELETE FROM Characters WHERE PlayerId > @first_id;
		DELETE FROM Players WHERE Id > @first_id;
    END

	IF @table_name = 'Characters'
    BEGIN
		SET @first_id = (SELECT MAX(Id) FROM Characters) - @no_of_rows;

		DELETE FROM CharactersInventoryItems WHERE CharacterId > @first_id;
		DELETE FROM Characters WHERE Id > @first_id;
    END

	IF @table_name = 'GuildsPlayers'
    BEGIN
		SET @first_id = (SELECT MAX(Id) FROM GuildsPlayers) - @no_of_rows;

		DELETE FROM GuildsPlayers WHERE Id > @first_id;
    END
END
GO

CREATE OR ALTER PROCEDURE select_view
@table_name varchar(50) 
AS
BEGIN        
	IF @table_name = 'Players'
    BEGIN
		SELECT * FROM ViewPlayers
    END

	IF @table_name = 'Characters'
    BEGIN
		SELECT * FROM ViewCharacters
    END

	IF @table_name = 'GuildsPlayers'
    BEGIN
		SELECT * FROM ViewGuildsPlayers
    END
END
GO

CREATE OR ALTER PROCEDURE run_tests
AS
BEGIN
	DECLARE @TestID int;
	DECLARE @TableID int;
	DECLARE @NoOfRows int;
	DECLARE @Position int;

	DECLARE test_cursor CURSOR FOR 
		SELECT *
		FROM TestTables;

	OPEN test_cursor;
	FETCH NEXT FROM test_cursor INTO @TestID, @TableID, @NoOfRows, @Position;

	DECLARE @test_name varchar(10);
	DECLARE @instruction varchar(32);

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @test_name = Name FROM Tests WHERE TestID = @TestId;
		SET @instruction = CONCAT('EXECUTE ', @test_name, ' ', @NoOfRows);
		EXEC(@instruction);

		FETCH NEXT FROM test_cursor INTO @TestID, @TableID, @NoOfRows, @Position;
	END;

	CLOSE test_cursor;
	DEALLOCATE test_cursor;
END
GO

EXECUTE run_tests;
