USE MMORPG
SET DATEFORMAT dmy;

-- SELECTS --
SELECT * FROM Players;
SELECT * FROM Guilds;
SELECT * FROM GuildsPlayers;
SELECT * FROM Attributes;
SELECT * FROM Characters;
SELECT * FROM Enemies;
SELECT * FROM Items;


-- INSERTS --
INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES('Scarlett', 'ac.fermentum@ac.org', '12/07/2020');
INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES('Mary', 'sed.libero.Proin@ridiculusmusDonec.net', '30/09/2020');
INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES('Signe', 'a.tortor.Nunc@Aeneangravidanunc.co.uk','30/11/2019');
INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES('Lance', 'eget.tincidunt.dui@interdum.com', '07/10/2020');
INSERT INTO Players([Name],[Email],[CreatedAt]) VALUES('Kermit', 'mollis.nec.cursus@egetipsumDonec.edu', '24/07/2020');

INSERT INTO Guilds([Name],[Description],[CreatedAt]) VALUES('WeAreNumberOne', 'The best guild.', '04/08/2019');
INSERT INTO Guilds([Name],[Description],[CreatedAt]) VALUES('TheTeam', 'Join us!', '06/06/2019');

INSERT INTO GuildsPlayers([GuildId],[PlayerId]) VALUES(1, 1);
INSERT INTO GuildsPlayers([GuildId],[PlayerId]) VALUES(1, 2);
INSERT INTO GuildsPlayers([GuildId],[PlayerId]) VALUES(2, 5);
INSERT INTO GuildsPlayers([GuildId],[PlayerId]) VALUES(1, 5);

INSERT INTO GuildsPlayers([GuildId],[PlayerId]) VALUES(2, 10);

-- ITEM ATTRIBUTES
INSERT INTO Attributes([Damage],[Dexterity]) VALUES(20, 2);
INSERT INTO Attributes([Health],[Defense],[Speed]) VALUES(80, 8, -2);
INSERT INTO Attributes([Health],[Attack],[Dexterity],[Speed]) VALUES(20, 2, 2, 4);
INSERT INTO Attributes([Damage],[Dexterity]) VALUES(10, 10);
-- CHARACTER ATTRIBUTES
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(200, 120, 30, 8, 20, 45, 33, 24);
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(180, 110, 23, 12, 24, 36, 25, 38);
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(120, 70, 12, 0, 20, 15, 16, 19);
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(300, 240, 40, 40, 35, 55, 40, 30);
-- ENEMY ATTRIBUTES
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(100, 10, 5, 5, 12, 6, 12, 12);
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(1000, 200, 30, 50, 30, 30, 40, 40);
INSERT INTO Attributes([Health],[Mana],[Attack],[Defense],[Speed],[Dexterity],[Vitality],[Wisdom]) VALUES(10000, 200, 80, 100, 20, 10, 60, 60);
----
INSERT INTO Characters([PlayerId],[AttributesId],[Name],[Lvl],[Xp],[Online]) VALUES(1, 4, 'NumberOne', 24, 783, 1);
INSERT INTO Characters([PlayerId],[AttributesId],[Name],[Lvl],[Xp],[Online]) VALUES(1, 5, 'NumberTwo', 12, 345, 0);
INSERT INTO Characters([PlayerId],[AttributesId],[Name],[Lvl],[Xp],[Online]) VALUES(2, 6, 'NumberThree', 33, 345, 1);
INSERT INTO Characters([PlayerId],[AttributesId],[Name],[Lvl],[Xp],[Online]) VALUES(5, 10, 'NumberFour', 4, 126, 0);

INSERT INTO Enemies([AttributesId],[Name],[Description]) VALUES(7, 'Dog', 'A dog.');
INSERT INTO Enemies([AttributesId],[Name],[Description]) VALUES(8, 'Werewolf', 'A powerful werewolf.');
INSERT INTO Enemies([AttributesId],[Name],[Description]) VALUES(11, 'Dragon', 'A very powerful dragon.');

INSERT INTO EnemiesInstances([EnemyId]) VALUES(1);
INSERT INTO EnemiesInstances([EnemyId]) VALUES(1);
INSERT INTO EnemiesInstances([EnemyId]) VALUES(1);
INSERT INTO EnemiesInstances([EnemyId]) VALUES(1);
INSERT INTO EnemiesInstances([EnemyId]) VALUES(1);
INSERT INTO EnemiesInstances([EnemyId]) VALUES(2);

INSERT INTO Items([AttributesId],[Name],[Description],[Type]) VALUES(1, 'Steel Sword', 'A sword made of steel.', 'SWORD');
INSERT INTO Items([AttributesId],[Name],[Description],[Type]) VALUES(2, 'Steel Armor', 'A heavy armor made of steel.', 'HEAVY_ARMOR');
INSERT INTO Items([AttributesId],[Name],[Description],[Type]) VALUES(3, 'Leather Armor', 'A ligt armor made of leather.', 'LIGHT_ARMOR');
INSERT INTO Items([AttributesId],[Name],[Description],[Type]) VALUES(9, 'Obsidian Dagger', 'A dagger made of obsidian.', 'DAGGER');

INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(1, 1);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(1, 1);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(1, 2);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(2, 1);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(2, 3);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(3, 3);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(3, 4);
INSERT INTO CharactersInventoryItems([CharacterId],[ItemId]) VALUES(4, 1);

-- UPDATES --
UPDATE Enemies
SET [Description] = 'A small dog.'
WHERE [Name] = 'Dog';

UPDATE Characters
SET [Name] = 'GoodName'
WHERE [Name] = 'NumberOne';

UPDATE Guilds
SET [PlayerCount] = (
	SELECT COUNT(*) FROM GuildsPlayers
	WHERE GuildsPlayers.[GuildId] = Guilds.[Id]
);


-- DELETES --
DELETE FROM Players;
DBCC CHECKIDENT (Players, RESEED, 0);
DELETE FROM Guilds;
DBCC CHECKIDENT (Guilds, RESEED, 0);
DELETE FROM Attributes;
DBCC CHECKIDENT (Attributes, RESEED, 0);
DELETE FROM Characters;
DBCC CHECKIDENT (Characters, RESEED, 0);
DELETE FROM Enemies;
DBCC CHECKIDENT (Enemies, RESEED, 0);
DELETE FROM Items;
DBCC CHECKIDENT (Items, RESEED, 0);

DELETE FROM Characters WHERE [AttributesId] = 10;

DELETE FROM EnemiesInstances WHERE [Id] = 1;
DELETE FROM Players
WHERE [Email] LIKE '%@interdum.com';

-- a. UNION
-- Show all swords and daggers
SELECT [Name], [Description] FROM Items
WHERE [Type] = 'SWORD' OR [Type] = 'Dagger'
ORDER BY [Name];

-- Show all players and all guilds
SELECT [Name], [CreatedAt] FROM Players
UNION
SELECT [Name], [CreatedAt] FROM Guilds
ORDER BY [Name];


-- b. INTERSECT
-- Show all attributes with damage, with a dexterity between 1 and 5
SELECT * FROM Attributes
WHERE [Damage] IS NOT NULL
INTERSECT
SELECT * FROM Attributes
WHERE [Dexterity] BETWEEN 1 AND 5;

-- Show all enemy dogs and cats.
SELECT * FROM Enemies
WHERE [Name] IN ('Dog', 'Cat');


-- c. DIFFERENCE
-- Show all enemies except dogs.
SELECT * FROM Enemies
EXCEPT
SELECT * FROM Enemies
WHERE [Name] = 'Dog';

-- Show all items that are not weapons.
SELECT * FROM Items
WHERE [Type] NOT IN ('SWORD', 'DAGGER');


-- d. JOINS
-- Show all players with their characters
SELECT Players.[Name] as [PlayerName], Characters.[Name] as [CharacterName]
FROM Players
FULL OUTER JOIN Characters
ON Players.[Id] = Characters.[PlayerId];

-- Show all players with their characters
SELECT Players.[Name] as [PlayerName], Characters.[Name] as [CharacterName]
FROM Players
LEFT OUTER JOIN Characters
ON Players.[Id] = Characters.[PlayerId];

-- Show all players that have characters with their characters
SELECT Players.[Name] as [PlayerName], Characters.[Name] as [CharacterName]
FROM Players
RIGHT OUTER JOIN Characters
ON Players.[Id] = Characters.[PlayerId];

-- Show all guilds and their players
SELECT Guilds.[Name] as [GuildName], Players.[Name] as [PlayerName]
FROM Guilds
INNER JOIN GuildsPlayers
ON Guilds.[Id] = GuildsPlayers.[GuildId]
INNER JOIN Players
ON Players.[Id] = GuildsPlayers.[PlayerId];

-- Show all the items of the guilds
SELECT Guilds.[Name] as [GuildName], Items.[Name] as [ItemName]
FROM Guilds
JOIN GuildsPlayers
ON GuildsPlayers.[GuildId] = Guilds.[Id]
JOIN Players
ON Players.[Id] = GuildsPlayers.[PlayerId]
JOIN Characters
ON Characters.[PlayerId] = Players.[Id]
JOIN CharactersInventoryItems
ON CharactersInventoryItems.[CharacterId] = Characters.[Id]
JOIN Items
ON Items.[Id] = CharactersInventoryItems.[ItemId];


-- e. IN, SUBQUERY
-- Show all enemies that are alive. (have an active instance)
SELECT * FROM Enemies
WHERE [Id] IN (SELECT [EnemyId] FROM EnemiesInstances);

-- Show all players that are in the guild 'WeAreNumberOne'
SELECT * FROM Players
WHERE [Id] IN (
	SELECT [PlayerId] FROM GuildsPlayers
	WHERE [GuildId] IN (
		SELECT [Id] FROM Guilds
		WHERE [Name] = 'WeAreNumberOne'
	)
);


-- f. EXISTS, SUBQUERY
-- Show all enemies that are alive. (have an active instance)
SELECT * FROM Enemies
WHERE EXISTS ( 
	SELECT * FROM EnemiesInstances
	WHERE [EnemyId] = Enemies.[Id]
);

-- Show all players that have an online character
SELECT * FROM Players
WHERE EXISTS (
	SELECT * FROM Characters
	WHERE [PlayerId] = Players.[Id] AND [Online] = 1
);


-- g. FROM, SUBQUERY
-- Show all the character names of the player 'Scarlett'
SELECT SC.[CharacterName]
FROM (
	SELECT Players.[Name] as [PlayerName], Characters.[Name] as [CharacterName]
	FROM Players
	FULL OUTER JOIN Characters
	ON Players.[Id] = Characters.[PlayerId]
) SC
WHERE SC.[PlayerName] = 'Scarlett';

-- Show all player names that are in the guild 'WeAreNumberOne'
SELECT WG.[PlayerName]
FROM (
	SELECT Guilds.[Name] as [GuildName], Players.[Name] as [PlayerName]
	FROM Guilds
	INNER JOIN GuildsPlayers
	ON Guilds.[Id] = GuildsPlayers.[GuildId]
	INNER JOIN Players
	ON Players.[Id] = GuildsPlayers.[PlayerId]
) WG
WHERE WG.[GuildName] = 'WeAreNumberOne';


-- h. GROUP BY
-- Show all the guilds and their members, grouped by guilds
SELECT Guilds.[Name] as [GuildName], Players.[Name] as [PlayerName]
FROM Guilds
INNER JOIN GuildsPlayers
ON Guilds.[Id] = GuildsPlayers.[GuildId]
INNER JOIN Players
ON Players.[Id] = GuildsPlayers.[PlayerId]
GROUP BY Guilds.[Name], Players.[Name];

-- Show how many characters each player has, if they have at least one
SELECT Players.[Name] as [PlayerName], COUNT(Characters.[Id]) as [CharactersCount]
FROM Players
LEFT OUTER JOIN Characters 
ON Players.[Id] = Characters.[PlayerId]
GROUP BY Players.[Name]
HAVING COUNT(Characters.[Id]) > 0
ORDER BY COUNT(Characters.[Id]) DESC;

-- Show the guild with the most players
SELECT TOP 1 Guilds.[Name] as [GuildName], COUNT(Players.[Id]) as [MembersCount]
FROM Guilds
INNER JOIN GuildsPlayers
ON Guilds.[Id] = GuildsPlayers.[GuildId]
INNER JOIN Players
ON Players.[Id] = GuildsPlayers.[PlayerId]
GROUP BY Guilds.[Name]
ORDER BY COUNT(Players.[Id]) DESC;


-- i. ANY and ALL
-- Show all characters that have more health than all enemies
SELECT Characters.[Name], Attributes.*
FROM Attributes
INNER JOIN Characters
ON Attributes.[Id] = Characters.[AttributesId]
WHERE Attributes.[Health] > ALL (
	SELECT Attributes.[Health]
	FROM Attributes
	INNER JOIN Enemies
	ON Attributes.[Id] = Enemies.[AttributesId]
);

-- Show all enemies that have more health than all characters
SELECT Enemies.[Name], Attributes.*
FROM Attributes
INNER JOIN Enemies
ON Attributes.[Id] = Enemies.[AttributesId]
WHERE Attributes.[Health] > ALL (
	SELECT Attributes.[Health]
	FROM Attributes
	INNER JOIN Characters
	ON Attributes.[Id] = Characters.[AttributesId]
);

-- Show all characters that have more health than any enemy
SELECT Characters.[Name], Attributes.*
FROM Attributes
INNER JOIN Characters
ON Attributes.[Id] = Characters.[AttributesId]
WHERE Attributes.[Health] > ANY (
	SELECT Attributes.[Health]
	FROM Attributes
	INNER JOIN Enemies
	ON Attributes.[Id] = Enemies.[AttributesId]
);

-- Show all enemies that have less health than any character
SELECT Enemies.[Name], Attributes.*
FROM Attributes
INNER JOIN Enemies
ON Attributes.[Id] = Enemies.[AttributesId]
WHERE Attributes.[Health] < ANY (
	SELECT Attributes.[Health]
	FROM Attributes
	INNER JOIN Characters
	ON Attributes.[Id] = Characters.[AttributesId]
);

