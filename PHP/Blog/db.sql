# Create db ericdb

DROP DATABASE IF EXISTS ericdb;

CREATE DATABASE ericdb;

USE ericdb;

# Dump of table blog_members
# ------------------------------------------------------------

DROP TABLE IF EXISTS `blog_members`;

CREATE TABLE `blog_members` (
  `memberID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`memberID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `blog_members` (`memberID`, `username`, `password`, `email`)
VALUES
  (1,'Eric','$2y$10$db3T5qK9Mhhj0y/FzIukGOb3.lxStbYRPoweNZcaGUWKY5gY2FWMO','ericbachmeier@hotmail.com');

# Dump of table blog_cats
# ------------------------------------------------------------

DROP TABLE IF EXISTS `blog_cats`;

CREATE TABLE `blog_cats` (
  `catID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `catTitle` varchar(255) DEFAULT NULL,
  `catSlug` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`catID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


INSERT INTO `blog_cats` (`catID`, `catTitle`, `catSlug`)
VALUES
  (1,'General','general'),
  (2,'Technology','technology'),
  (3,'Miscallaneous','miscallaneous'),
  (4,'Programming','programming'),
  (5,'Hockey','hockey'),
  (6,'School','school'),
  (7,'Jobs','jobs');

# Dump of table blog_post_cats
# ------------------------------------------------------------

DROP TABLE IF EXISTS `blog_post_cats`;

CREATE TABLE `blog_post_cats` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `postID` int(11) DEFAULT NULL,
  `catID` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `blog_post_cats` (`id`, `postID`, `catID`)
VALUES
  (1,1,2),
  (2,1,6);

# Dump of table blog_posts
# ------------------------------------------------------------

DROP TABLE IF EXISTS `blog_posts`;

CREATE TABLE `blog_posts` (
  `postID` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `postTitle` varchar(255) DEFAULT NULL,
  `postSlug` varchar(255) DEFAULT NULL,
  `postDesc` text,
  `postCont` text,
  `postDate` datetime DEFAULT NULL,
  PRIMARY KEY (`postID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `blog_posts` (`postID`, `postTitle`, `postSlug`, `postDesc`, `postCont`, `postDate`)
VALUES
  (1,
   'Title',
   'title-slugged',
   '<p>Content</p>',
   '2016-04-04 23:18:14');
