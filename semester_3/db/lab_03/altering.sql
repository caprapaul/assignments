USE MMORPG;
GO

ALTER PROCEDURE do_version_1
AS
BEGIN
	ALTER TABLE Players
	ALTER COLUMN [Email] varchar(128)
	PRINT 'Changed Email column to varchar(128)';
END

GO

ALTER PROCEDURE undo_version_1
AS
BEGIN
	ALTER TABLE Players
	ALTER COLUMN [Email] varchar(64)
	PRINT 'Changed Email column to varchar(64)';
END

GO

ALTER PROCEDURE do_version_2
AS
BEGIN
	ALTER TABLE Players
	ADD CharacterCount int
	PRINT 'Added CharacterCount column to Players table.';
END

GO

ALTER PROCEDURE undo_version_2
AS
BEGIN
	ALTER TABLE Players
	DROP COLUMN CharacterCount
	PRINT 'Removed CharacterCount column from Players table.';
END

GO
USE [MMORPG]
GO

ALTER PROCEDURE do_version_3
AS
BEGIN
	ALTER TABLE Guilds
	ADD CONSTRAINT df_Description DEFAULT 'A guild.' 
	FOR [Description];
	PRINT 'Set default Description to Guilds table.';
END

GO

ALTER PROCEDURE undo_version_3
AS
BEGIN
	ALTER TABLE Guilds
	DROP CONSTRAINT df_Description;
	PRINT 'Removed default Description from Guilds table.';
END

GO

ALTER PROCEDURE do_version_4
AS
BEGIN
	ALTER TABLE GuildsPlayers
	DROP CONSTRAINT [PK__GuildsPl__3214EC07526B2A09]
	PRINT 'Removed primary key from GuildsPlayers table.';
END

GO

ALTER PROCEDURE undo_version_4
AS
BEGIN
	ALTER TABLE GuildsPlayers
	ADD CONSTRAINT [PK__GuildsPl__3214EC07526B2A09] PRIMARY KEY(Id)
	PRINT 'Added Id column as primary key for GuildsPlayers table.';
END

GO

ALTER PROCEDURE do_version_5
AS
BEGIN
	ALTER TABLE Players
	ADD CONSTRAINT ck_PlayersName UNIQUE (Name);
    print 'Add Name as candidate key to Players table';
END

GO

ALTER PROCEDURE undo_version_5
AS
BEGIN
	ALTER TABLE Players
	DROP CONSTRAINT ck_PlayersName
    print 'Remove Name candidate key from Players table';
END

GO
USE [MMORPG]
GO

ALTER PROCEDURE do_version_6
AS
BEGIN
	ALTER TABLE Characters
	DROP CONSTRAINT [FK__Character__Attri__19AACF41];
    PRINT 'Removed Attributes foreign key from Characters table.';
END

GO

ALTER PROCEDURE undo_version_6
AS
BEGIN
	ALTER TABLE Characters
	ADD CONSTRAINT [FK__Character__Attri__19AACF41] FOREIGN KEY(AttributesId) REFERENCES Attributes(Id);
    PRINT 'Added Attributes as foreign key for Characters table.';
END

GO

ALTER PROCEDURE do_version_7
AS
BEGIN
	CREATE TABLE World(
		Id int PRIMARY KEY IDENTITY,
		Name varchar(32) NOT NULL,
		Description varchar(128)
	);
    PRINT 'Added World table.';
END

GO

ALTER PROCEDURE undo_version_7
AS
BEGIN
	DROP TABLE World;
    PRINT 'Removed World table.';
END

GO

ALTER PROCEDURE main 
@version int
AS 
BEGIN
	IF @version < 0 OR @version > 7
	BEGIN
		RAISERROR('Invalid version', 16, 1);
		RETURN;
	END

	DECLARE @currentVersion INT;
	SET @currentVersion = (SELECT [Value] FROM Version);

	IF @version = @currentVersion
	BEGIN
		PRINT CONCAT('Already at version ', @version);
		RETURN;
	END

	DECLARE @instruction varchar(32);

	WHILE @currentVersion < @version
	BEGIN
		SET @currentVersion = @currentVersion + 1
		SET @instruction = CONCAT('EXECUTE do_version_', @currentVersion);
		EXEC(@instruction);
	END

	WHILE @currentVersion > @version
	BEGIN
		SET @instruction = CONCAT('EXECUTE undo_version_', @currentVersion);
		EXEC(@instruction);
		SET @currentVersion = @currentVersion - 1
	END

	UPDATE Version
	SET [Value] = @currentVersion;

	PRINT CONCAT('Changed to version ', @currentVersion);
END

GO

EXECUTE main 0;

CREATE TABLE Version(
	Value int
);

SELECT * FROM Version;

INSERT INTO Version VALUES(0);

