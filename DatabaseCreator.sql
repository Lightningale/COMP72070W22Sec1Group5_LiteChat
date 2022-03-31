DROP DATABASE IF EXISTS `LiteChat`;
CREATE DATABASE `LiteChat`; 
USE `LiteChat`;

SET NAMES utf8 ;
SET character_set_client = utf8mb4 ;

CREATE TABLE `Users`(
`username` varchar(20) NOT NULL PRIMARY KEY,
`password` varchar(20) NOT NULL
)ENGINE=InnoDB;
CREATE TABLE `Chatrooms`(
`roomID` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
`name` varchar(20) NOT NULL,
`owner` varchar(20) NOT NULL,
FOREIGN KEY (`owner`) REFERENCES `Users` (`username`)
)ENGINE=InnoDB;
CREATE TABLE `RoomMembers`(
`ID` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
`roomID` INT NOT NULL,
`username` varchar(20) NOT NULL,
FOREIGN KEY (`roomID`) REFERENCES `Chatrooms` (`roomID`) ON DELETE CASCADE,
FOREIGN KEY (`username`) REFERENCES `Users` (`username`)ON DELETE CASCADE
)ENGINE=InnoDB;
CREATE TABLE `Messages`(
`ID` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
`roomID` INT NOT NULL,
`username` varchar(20) NOT NULL,
`timestamp` DATETIME NOT NULL,
`message` varchar(200),
FOREIGN KEY (`roomID`) REFERENCES `Chatrooms` (`roomID`) ON DELETE CASCADE,
FOREIGN KEY (`username`) REFERENCES `Users` (`username`)
)ENGINE=InnoDB;



GRANT SELECT, INSERT, CREATE, DROP ON `LiteChat`.* TO connector@localhost;
SHOW GRANTS for connector@localhost;
INSERT INTO Users VALUES('geyang',"geyangpassword");
INSERT INTO Users VALUES('shane',"shanepassword");
select * from chatrooms;
select * from roomMembers;