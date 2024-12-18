create table ridership(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2029-04','2029-03','2029-02','2029-01','2028-12','2028-11','2028-10','2028-09','2028-08','2028-07','2028-06','2028-05','2028-04','2028-03','2028-02','2028-01','2027-12','2027-11','2027-10','2027-09','2027-08','2027-07','2027-06','2027-05','2027-04','2027-03','2027-02','2027-01','2026-12','2026-11','2026-10','2026-09','2026-08','2026-07','2026-06','2026-05','2026-04','2026-03','2026-02','2026-01','2025-12','2025-11','2025-10','2025-09','2025-08','2025-07','2025-06','2025-05','2025-04','2025-03','2025-02','2025-01','2024-12','2024-11','2024-10','2024-09','2024-08','2024-07','2024-06','2024-05','2024-04','2024-03','2024-02','2024-01','2023-12','2023-11','2023-10','2023-09','2023-08','2023-07','2023-06','2023-05','2023-04','2023-03','2023-02','2023-01','2022-12','2022-11','2022-10','2022-09','2022-08','2022-07','2022-06','2022-05','2022-04','2022-03','2022-02','2022-01','2021-12','2021-11','2021-10','2021-09','2021-08','2021-07','2021-06','2021-05','2021-04','2021-03','2021-02','2021-01','2020-12','2020-11','2020-10','2020-09','2020-08','2020-07','2020-06','2020-05','2020-04','2020-03','2020-02','2020-01','2019-12','2019-11','2019-10','2019-09','2019-08','2019-07','2019-06','2019-05','2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  entry_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  exit_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  rider_count int(11) not null,
  unique mtee(monthfull, day_type, entry_station_code, exit_station_code),
  index ee(entry_station_code, exit_station_code),
  index me1(monthfull, entry_station_code),
  index me2(monthfull, exit_station_code)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;

create table ridership_entry_total(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2029-04','2029-03','2029-02','2029-01','2028-12','2028-11','2028-10','2028-09','2028-08','2028-07','2028-06','2028-05','2028-04','2028-03','2028-02','2028-01','2027-12','2027-11','2027-10','2027-09','2027-08','2027-07','2027-06','2027-05','2027-04','2027-03','2027-02','2027-01','2026-12','2026-11','2026-10','2026-09','2026-08','2026-07','2026-06','2026-05','2026-04','2026-03','2026-02','2026-01','2025-12','2025-11','2025-10','2025-09','2025-08','2025-07','2025-06','2025-05','2025-04','2025-03','2025-02','2025-01','2024-12','2024-11','2024-10','2024-09','2024-08','2024-07','2024-06','2024-05','2024-04','2024-03','2024-02','2024-01','2023-12','2023-11','2023-10','2023-09','2023-08','2023-07','2023-06','2023-05','2023-04','2023-03','2023-02','2023-01','2022-12','2022-11','2022-10','2022-09','2022-08','2022-07','2022-06','2022-05','2022-04','2022-03','2022-02','2022-01','2021-12','2021-11','2021-10','2021-09','2021-08','2021-07','2021-06','2021-05','2021-04','2021-03','2021-02','2021-01','2020-12','2020-11','2020-10','2020-09','2020-08','2020-07','2020-06','2020-05','2020-04','2020-03','2020-02','2020-01','2019-12','2019-11','2019-10','2019-09','2019-08','2019-07','2019-06','2019-05','2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  entry_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  rider_count int(11) not null,
  unique `med` (monthfull, entry_station_code, day_type)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;


create table ridership_exit_total(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2029-04','2029-03','2029-02','2029-01','2028-12','2028-11','2028-10','2028-09','2028-08','2028-07','2028-06','2028-05','2028-04','2028-03','2028-02','2028-01','2027-12','2027-11','2027-10','2027-09','2027-08','2027-07','2027-06','2027-05','2027-04','2027-03','2027-02','2027-01','2026-12','2026-11','2026-10','2026-09','2026-08','2026-07','2026-06','2026-05','2026-04','2026-03','2026-02','2026-01','2025-12','2025-11','2025-10','2025-09','2025-08','2025-07','2025-06','2025-05','2025-04','2025-03','2025-02','2025-01','2024-12','2024-11','2024-10','2024-09','2024-08','2024-07','2024-06','2024-05','2024-04','2024-03','2024-02','2024-01','2023-12','2023-11','2023-10','2023-09','2023-08','2023-07','2023-06','2023-05','2023-04','2023-03','2023-02','2023-01','2022-12','2022-11','2022-10','2022-09','2022-08','2022-07','2022-06','2022-05','2022-04','2022-03','2022-02','2022-01','2021-12','2021-11','2021-10','2021-09','2021-08','2021-07','2021-06','2021-05','2021-04','2021-03','2021-02','2021-01','2020-12','2020-11','2020-10','2020-09','2020-08','2020-07','2020-06','2020-05','2020-04','2020-03','2020-02','2020-01','2019-12','2019-11','2019-10','2019-09','2019-08','2019-07','2019-06','2019-05','2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  exit_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  rider_count int(11) not null,
  unique `med` (monthfull, exit_station_code, day_type)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;

create table ridership_total(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2029-04','2029-03','2029-02','2029-01','2028-12','2028-11','2028-10','2028-09','2028-08','2028-07','2028-06','2028-05','2028-04','2028-03','2028-02','2028-01','2027-12','2027-11','2027-10','2027-09','2027-08','2027-07','2027-06','2027-05','2027-04','2027-03','2027-02','2027-01','2026-12','2026-11','2026-10','2026-09','2026-08','2026-07','2026-06','2026-05','2026-04','2026-03','2026-02','2026-01','2025-12','2025-11','2025-10','2025-09','2025-08','2025-07','2025-06','2025-05','2025-04','2025-03','2025-02','2025-01','2024-12','2024-11','2024-10','2024-09','2024-08','2024-07','2024-06','2024-05','2024-04','2024-03','2024-02','2024-01','2023-12','2023-11','2023-10','2023-09','2023-08','2023-07','2023-06','2023-05','2023-04','2023-03','2023-02','2023-01','2022-12','2022-11','2022-10','2022-09','2022-08','2022-07','2022-06','2022-05','2022-04','2022-03','2022-02','2022-01','2021-12','2021-11','2021-10','2021-09','2021-08','2021-07','2021-06','2021-05','2021-04','2021-03','2021-02','2021-01','2020-12','2020-11','2020-10','2020-09','2020-08','2020-07','2020-06','2020-05','2020-04','2020-03','2020-02','2020-01','2019-12','2019-11','2019-10','2019-09','2019-08','2019-07','2019-06','2019-05','2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  rider_count int(11) not null,
  unique `md` (monthfull, day_type)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;

create table stations(
  code_2l varchar(2) not null,
  code_4l varchar(4) not null,
  code_long varchar(6) not null,
  ordinary_name varchar(100) not null,
  wikipedia_page varchar(100) not null,
  bart_page varchar(100) not null,
  airport boolean default false, 
  muni_connection boolean default false,
  caltrain_connection boolean default false,
  amtrak_connection boolean default false,
  vta_light_rail_connection boolean default false,
  end_of_line boolean default false,
  trains_can_turn boolean,
  opening_date date
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;

create table routes(
  start_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  end_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  time_from_start int(11) not null
) ENGINE=InnoDB AUTO_INCREMENT=14342355 DEFAULT CHARSET=utf8mb4;

create table fares(
  start_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  end_station_code enum('12','16','19','24','AN','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PC','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  fare float(5,2),
  effective_date date not null,
  unique `sed` (start_station_code, end_station_code, effective_date)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;

/*
create table sps(
  station_code enum('12','16','19','24','AS','BE','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','ML','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  study_year enum('2015','2008','1998') not null,
  home_entry_fracton float(3,2),
  home_walk_access_mode float(3,2),
  home_bike_access_mode float(3,2),
  home_transit_access_mode float(3,2),
  home_motorbike_access_mode float(3,2),
  home_drive_access_mode float(3,2),
  home_dropoff_access_mode float(3,2),
  home_median_distance_in_miles float(4,2),
  destination_purpose_workplace float(3,2),
  destination_purpose_work_related float(3,2),
  destination_purpose_college float(3,2),
  destination_purpose_school float(3,2),
  destination_purpose_shopping float(3,2),
  destination_purpose_sports float(3,2),
  destination_purpose_restaurant float(3,2),
  destination_purpose_theater float(3,2),
  destination_purpose_friends_family float(3,2),
  destination_purpose_medical float(3,2),
  destination_purpose_errands float(3,2),
  destination_purpose_airplane float(3,2),
  destination_purpose_hotel float(3,2),
  destination_purpose_escorting float(3,2),
  destination_purpose_other float(3,2),
*/
