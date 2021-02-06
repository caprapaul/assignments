CREATE DATABASE MMORPG
GO
USE MMORPG

DROP TABLE Players
DROP TABLE Guilds
DROP TABLE GuildsPlayers
DROP TABLE Attributes
DROP TABLE Characters
DROP TABLE Items
DROP TABLE CharactersEquippedItems
DROP TABLE CharactersInventoryItems
DROP TABLE Enemies
DROP TABLE EnemiesDropItems
DROP TABLE EnemiesInstances

CREATE TABLE Players (
	Id int PRIMARY KEY IDENTITY,
	Name varchar(32) UNIQUE NOT NULL,
	Email varchar(64) NOT NULL,
	CreatedAt date
)

CREATE TABLE Guilds (
	Id int PRIMARY KEY IDENTITY,
	Name varchar(32) UNIQUE NOT NULL,
	Description varchar(128) NOT NULL,
	CreatedAt date,
	PlayerCount int,
)

CREATE TABLE GuildsPlayers (
	Id int PRIMARY KEY IDENTITY,
	GuildId int FOREIGN KEY REFERENCES Guilds(Id),
	PlayerId int FOREIGN KEY REFERENCES Players(Id),
)

CREATE TABLE Attributes (
	Id int PRIMARY KEY IDENTITY,
	Damage int,
	Health int,
	Mana int,
	Attack int,
	Defense int,
	Speed int,
	Dexterity int,
	Vitality int,
	Wisdom int
)

CREATE TABLE Characters (
	Id int PRIMARY KEY IDENTITY,
	PlayerId int FOREIGN KEY REFERENCES Players(Id),
	AttributesId int FOREIGN KEY REFERENCES Attributes(Id),
	Name varchar(32) UNIQUE NOT NULL,
	Lvl int NOT NULL,
	Xp int NOT NULL,
	Online bit,
)

CREATE TABLE Items (
	Id int PRIMARY KEY IDENTITY,
	Name varchar(32) UNIQUE NOT NULL,
	Description varchar(128),
	Type varchar(16) NOT NULL,
	AttributesId int FOREIGN KEY REFERENCES Attributes(Id),
)

CREATE TABLE CharactersEquippedItems (
	Id int PRIMARY KEY IDENTITY,
	CharacterId int FOREIGN KEY REFERENCES Characters(Id),
	ItemId int FOREIGN KEY REFERENCES Items(Id),
)

CREATE TABLE CharactersInventoryItems (
	Id int PRIMARY KEY IDENTITY,
	CharacterId int FOREIGN KEY REFERENCES Characters(Id),
	ItemId int FOREIGN KEY REFERENCES Items(Id),
)

CREATE TABLE Enemies (
	Id int PRIMARY KEY IDENTITY,
	Name varchar(32) UNIQUE NOT NULL,
	Description varchar(128),
	AttributesId int FOREIGN KEY REFERENCES Attributes(Id),
)

CREATE TABLE EnemiesDropItems (
	Id int PRIMARY KEY IDENTITY,
	EnemyId int FOREIGN KEY REFERENCES Enemies(Id),
	ItemId int FOREIGN KEY REFERENCES Items(Id),
)


CREATE TABLE EnemiesInstances (
	Id int PRIMARY KEY IDENTITY,
	EnemyId int FOREIGN KEY REFERENCES Enemies(Id),
)

