-- MySQL dump 10.13  Distrib 5.7.9, for Win32 (AMD64)
--
-- Host: localhost    Database: db_pcserver
-- ------------------------------------------------------
-- Server version	5.6.29-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `data_log`
--

DROP TABLE IF EXISTS `data_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data_log` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `person` varchar(45) NOT NULL,
  `version` varchar(45) DEFAULT NULL,
  `log_string` varchar(45) NOT NULL,
  `created_dttm` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data_log`
--

LOCK TABLES `data_log` WRITE;
/*!40000 ALTER TABLE `data_log` DISABLE KEYS */;
INSERT INTO `data_log` VALUES (1,'dinglinhui','1','created','2015-05-25 14:38:57.296'),(2,'vasu.babu@alskdj.com','2','lkjsdlkfjjlkskfdj','2015-05-25 14:38:57.296'),(3,'vasu.babu@alskdj.com','3','lkjsdlkfjjlkskfdj','2015-05-25 14:39:06.294');
/*!40000 ALTER TABLE `data_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dog`
--

DROP TABLE IF EXISTS `dog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dog` (
  `id` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  `type` varchar(45) DEFAULT NULL,
  `color` varchar(45) DEFAULT NULL,
  `weight` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dog`
--

LOCK TABLES `dog` WRITE;
/*!40000 ALTER TABLE `dog` DISABLE KEYS */;
INSERT INTO `dog` VALUES (21,'小不点','藏獒','灰色',25);
/*!40000 ALTER TABLE `dog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employee` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `NAME` varchar(45) NOT NULL,
  `JOINING_DATE` datetime NOT NULL,
  `SALARY` double NOT NULL,
  `SSN` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `SSN_UNIQUE` (`SSN`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (1,'dinglinhui','2015-05-25 00:00:00',100000,'1');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person`
--

DROP TABLE IF EXISTS `person`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `person` (
  `id` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `person`
--

LOCK TABLES `person` WRITE;
/*!40000 ALTER TABLE `person` DISABLE KEYS */;
INSERT INTO `person` VALUES (1,'dinglinhui',27,'shanghai'),(6,'大象hadoop',10,'家住Apache基金组织');
/*!40000 ALTER TABLE `person` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_admin`
--

DROP TABLE IF EXISTS `tb_admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_admin` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `admin_id` varchar(45) NOT NULL,
  `admin_name` varchar(45) DEFAULT NULL,
  `admin_level` int(11) DEFAULT '2',
  `admin_passwd` varchar(100) DEFAULT NULL,
  `admin_logindate` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`,`admin_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_admin`
--

LOCK TABLES `tb_admin` WRITE;
/*!40000 ALTER TABLE `tb_admin` DISABLE KEYS */;
INSERT INTO `tb_admin` VALUES (1,'root','root',0,'cm9vdA==','Fri Mar 20 05:29:26 2015 GMT'),(2,'admin','admin',1,'YWRtaW4=','Fri Mar 20 05:41:49 2015 GMT'),(3,'teacher','teacher',2,'YWRtaW4=','Thu Mar 5 09:30:29 2015 GMT'),(4,'dinglinhui','dinglinhui',3,'YWRtaW4=',NULL);
/*!40000 ALTER TABLE `tb_admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_exam`
--

DROP TABLE IF EXISTS `tb_exam`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_exam` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `exam_id` varchar(45) NOT NULL,
  `exam_date` varchar(45) DEFAULT NULL,
  `exam_status` int(11) DEFAULT NULL,
  `exam_name` varchar(200) DEFAULT NULL,
  `exam_room` varchar(45) DEFAULT NULL,
  `exam_teacher` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`,`exam_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_exam`
--

LOCK TABLES `tb_exam` WRITE;
/*!40000 ALTER TABLE `tb_exam` DISABLE KEYS */;
INSERT INTO `tb_exam` VALUES (1,'20150301100001','2015-03-01 10:00:00',2,'15年3月份地铁模拟驾驶三维仿真培训考试 第一场','room 1','Jack'),(2,'20150301100002','2015-03-01 10:00:00',2,'15年3月份地铁模拟驾驶三维仿真培训考试 第二场','room 2','Kevin');
/*!40000 ALTER TABLE `tb_exam` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_user`
--

DROP TABLE IF EXISTS `tb_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` varchar(45) NOT NULL,
  `user_name` varchar(45) DEFAULT NULL,
  `user_password` varchar(45) DEFAULT NULL,
  `user_authorithy` varchar(45) DEFAULT NULL,
  `exam_id` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`,`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=201 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_user`
--

LOCK TABLES `tb_user` WRITE;
/*!40000 ALTER TABLE `tb_user` DISABLE KEYS */;
INSERT INTO `tb_user` VALUES (101,'80201','包俊杰','123456','7',''),(102,'80202','金玲玲','123456','7',''),(103,'80203','范文斌','123456','7',''),(104,'80204','徐玉凤','123456','7',''),(105,'80205','窦莹','123456','7',''),(106,'80206','戴可珺','123456','7',''),(107,'80207','张函玉','123456','7',''),(108,'80208','范书成','123456','7',''),(109,'80209','胡汝伟','123456','7',''),(110,'80210','李仁强','123456','7',''),(111,'80211','林俊亦','123456','7',''),(112,'80212','张馨','123456','7',''),(113,'80213','程呈','123456','7',''),(114,'80214','徐磊','123456','7',''),(115,'80215','潘婧','123456','7',''),(116,'80216','吴立坤','123456','7',''),(117,'80217','倪珊','123456','7',''),(118,'80218','刘玮','123456','7',''),(119,'80219','张彩艳','123456','7',''),(120,'80220','孙晶','123456','7',''),(121,'80221','岳晨云','123456','7',''),(122,'80222','张舒','123456','7',''),(123,'80223','程锦翔','123456','7',''),(124,'80224','胡月','123456','7',''),(125,'80225','冯英收','123456','7',''),(126,'80226','钱冬冬','123456','7',''),(127,'80227','陈鹏','123456','7',''),(128,'80228','徐俊琴','123456','7',''),(129,'80229','葛敏敏','123456','7',''),(130,'80230','许萌君','123456','7',''),(131,'80231','蔡秀琴','123456','7',''),(132,'80232','王莹','123456','7',''),(133,'80233','杜艳玲','123456','7',''),(134,'80234','吴盖','123456','7',''),(135,'80235','秦红文','123456','7',''),(136,'80236','周游','123456','7',''),(137,'80237','王树彪','123456','7',''),(138,'80238','张军','123456','7',''),(139,'80239','谢燕军','123456','7',''),(140,'80240','束宇','123456','7',''),(141,'80241','王强','123456','7',''),(142,'80242','张铮','123456','7',''),(143,'80243','朱斌','123456','7',''),(144,'80244','夏玲玲','123456','7',''),(145,'80245','张易天','123456','7',''),(146,'80246','魏星','123456','7',''),(147,'80247','翁永清','123456','7',''),(148,'80248','陈盛慧','123456','7',''),(149,'80249','李燕','123456','7',''),(150,'80250','孙梦琛','123456','7',''),(151,'80251','王学峰','123456','7',''),(152,'80252','钱万祥','123456','7',''),(153,'80253','余倩','123456','7',''),(154,'80254','吴梦笔','123456','7',''),(155,'80255','黄建萍','123456','7',''),(156,'80256','朱小飞','123456','7',''),(157,'80257','薛璐','123456','7',''),(158,'80258','秦琳','123456','7',''),(159,'80259','廉志媛','123456','7',''),(160,'80260','倪洋','123456','7',''),(161,'80261','朱亮亮','123456','7',''),(162,'80262','季亚楠','123456','7',''),(163,'80263','孟凡','123456','7',''),(164,'80264','黄艳芳','123456','7',''),(165,'80265','查婷','123456','7',''),(166,'80266','高文晨','123456','7',''),(167,'80267','石腊梅','123456','7',''),(168,'80268','张红','123456','7',''),(169,'80269','许光第','123456','7',''),(170,'80270','包俊杰','123456','7',''),(171,'80271','金玲玲','123456','7',''),(172,'80272','范文斌','123456','7',''),(173,'80273','徐玉凤','123456','7',''),(174,'80274','窦莹','123456','7',''),(175,'80275','戴可珺','123456','7',''),(176,'80276','张函玉','123456','7',''),(177,'80277','范书成','123456','7',''),(178,'80278','胡汝伟','123456','7',''),(179,'80279','李仁强','123456','7',''),(180,'80280','林俊亦','123456','7',''),(181,'80281','张馨','123456','7',''),(182,'80282','程呈','123456','7',''),(183,'80283','徐磊','123456','7',''),(184,'80284','潘婧','123456','7',''),(185,'80285','吴立坤','123456','7',''),(186,'80286','倪珊','123456','7',''),(187,'80287','刘玮','123456','7',''),(188,'80288','张彩艳','123456','7',''),(189,'80289','孙晶','123456','7',''),(190,'80290','岳晨云','123456','7',''),(191,'80291','张舒','123456','7',''),(192,'80292','程锦翔','123456','7',''),(193,'80293','胡月','123456','7',''),(194,'80294','冯英收','123456','7',''),(195,'80295','钱冬冬','123456','7',''),(196,'80296','陈鹏','123456','7',''),(197,'80297','徐俊琴','123456','7',''),(198,'80298','葛敏敏','123456','7',''),(199,'80299','许萌君','123456','7',''),(200,'80300','许萌君','123456','7','');
/*!40000 ALTER TABLE `tb_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_user_exam_201503`
--

DROP TABLE IF EXISTS `tb_user_exam_201503`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_user_exam_201503` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` varchar(45) DEFAULT NULL,
  `user_opearte` varchar(45) DEFAULT NULL,
  `exam_score` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_user_exam_201503`
--

LOCK TABLES `tb_user_exam_201503` WRITE;
/*!40000 ALTER TABLE `tb_user_exam_201503` DISABLE KEYS */;
INSERT INTO `tb_user_exam_201503` VALUES (1,'202060208',NULL,'99');
/*!40000 ALTER TABLE `tb_user_exam_201503` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-06-27 17:44:45
