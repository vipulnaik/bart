create table ridership(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  entry_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  exit_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  ridercount int(11) not null,
  unique mtee(monthfull, day_type, entry_station_code, exit_station_code)
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

create table ridership_entry_total(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  entry_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  ridercount int(11) not null,
  unique `med` (monthfull, entry_station_code, day_type)
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


create table ridership_exit_total(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  exit_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  ridercount int(11) not null,
  unique `med` (monthfull, exit_station_code, day_type)
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

create table ridership_total(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull enum('2019-04','2019-03','2019-02','2019-01','2018-12','2018-11','2018-10','2018-09','2018-08','2018-07','2018-06','2018-05','2018-04','2018-03','2018-02','2018-01','2017-12','2017-11','2017-10','2017-09','2017-08','2017-07','2017-06','2017-05','2017-04','2017-03','2017-02','2017-01','2016-12','2016-11','2016-10','2016-09','2016-08','2016-07','2016-06','2016-05','2016-04','2016-03','2016-02','2016-01','2015-12','2015-11','2015-10','2015-09','2015-08','2015-07','2015-06','2015-05','2015-04','2015-03','2015-02','2015-01','2014-12','2014-11','2014-10','2014-09','2014-08','2014-07','2014-06','2014-05','2014-04','2014-03','2014-02','2014-01','2013-12','2013-11','2013-10','2013-09','2013-08','2013-07','2013-06','2013-05','2013-04','2013-03','2013-02','2013-01','2012-12','2012-11','2012-10','2012-09','2012-08','2012-07','2012-06','2012-05','2012-04','2012-03','2012-02','2012-01','2011-12','2011-11','2011-10','2011-09','2011-08','2011-07','2011-06','2011-05','2011-04','2011-03','2011-02','2011-01','2010-12','2010-11','2010-10','2010-09','2010-08','2010-07','2010-06','2010-05','2010-04','2010-03','2010-02','2010-01','2009-12','2009-11','2009-10','2009-09','2009-08','2009-07','2009-06','2009-05','2009-04','2009-03','2009-02','2009-01','2008-12','2008-11','2008-10','2008-09','2008-08','2008-07','2008-06','2008-05','2008-04','2008-03','2008-02','2008-01','2007-12','2007-11','2007-10','2007-09','2007-08','2007-07','2007-06','2007-05','2007-04','2007-03','2007-02','2007-01','2006-12','2006-11','2006-10','2006-09','2006-08','2006-07','2006-06','2006-05','2006-04','2006-03','2006-02','2006-01','2005-12','2005-11','2005-10','2005-09','2005-08','2005-07','2005-06','2005-05','2005-04','2005-03','2005-02','2005-01','2004-12','2004-11','2004-10','2004-09','2004-08','2004-07','2004-06','2004-05','2004-04','2004-03','2004-02','2004-01','2003-12','2003-11','2003-10','2003-09','2003-08','2003-07','2003-06','2003-05','2003-04','2003-03','2003-02','2003-01','2002-12','2002-11','2002-10','2002-09','2002-08','2002-07','2002-06','2002-05','2002-04','2002-03','2002-02','2002-01','2001-12','2001-11','2001-10','2001-09','2001-08','2001-07','2001-06','2001-05','2001-04','2001-03','2001-02','2001-01') not null,
  day_type enum('weekday','saturday','sunday'),
  ridercount int(11) not null,
  unique `md` (monthfull, day_type)
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

truncate table ridership_entry_total;
insert into ridership_entry_total(monthfull, entry_station_code, day_type, ridercount) select monthfull, entry_station_code, day_type, sum(ridercount) from ridership group by monthfull, entry_station_code, day_type;
truncate table ridership_exit_total;
insert into ridership_exit_total(monthfull, exit_station_code, day_type, ridercount) select monthfull, exit_station_code, day_type, sum(ridercount) from ridership group by monthfull, exit_station_code, day_type;
truncate table ridership_total;
insert into ridership_total(monthfull, day_type, ridercount) select monthfull, day_type, sum(ridercount) from ridership group by monthfull, day_type;


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
  end_of_line boolean default false,
  trains_can_turn boolean,
  opening_date date
) ENGINE=InnoDB AUTO_INCREMENT=14342245 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

create table routes(
  start_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  end_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  time_from_start int(11) not null
) ENGINE=InnoDB AUTO_INCREMENT=14342355 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

create table fares(
  start_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  end_station_code enum('12','16','19','24','AS','BF','BK','BP','CC','CL','CM','CN','CV','DC','ED','EM','EN','EP','FM','FV','GP','HY','LF','LM','MA','MB','MT','NB','NC','OA','OR','OW','PH','PL','RM','RR','SB','SH','SL','SO','SS','UC','WC','WD','WP','WS') not null,
  fare float(5,2),
  effective_date date not null
) ENGINE=InnoDB AUTO_INCREMENT=12742355 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

insert into stations(code_2l, code_4l, code_long, ordinary_name, wikipedia_page, bart_page, airport, muni_connection, caltrain_connection, amtrak_connection, end_of_line, trains_can_turn, opening_date) values
  ('RM','RICH','RICH','Richmond','https://en.wikipedia.org/wiki/Richmond_station_(California)','https://www.bart.gov/stations/rich',false,false,false,true,true,true,'1973-01-29'),
  ('EN','DELN','DEL N','El Cerrito del Norte','https://en.wikipedia.org/wiki/El_Cerrito_del_Norte_(BART_station)','https://www.bart.gov/stations/deln',false,false,false,false,false,NULL,'1973-01-29'),
  ('EP','PLZA','PLAZA','El Cerrito Plaza','https://en.wikipedia.org/wiki/El_Cerrito_Plaza_station','https://www.bart.gov/stations/plza',false,false,false,false,false,NULL,'1973-01-29'),
  ('NB','NBRK','N BRK','North Berkeley','https://en.wikipedia.org/wiki/North_Berkeley_station','https://www.bart.gov/stations/nbrk',false,false,false,false,false,false,'1973-01-29'),
  ('BK','DBRK','BRK','Downtown Berkeley','https://en.wikipedia.org/wiki/Downtown_Berkeley_station','https://www.bart.gov/stations/dbrk',false,false,false,false,false,false,'1973-01-29'),
  ('AS','ASHB','ASHBY','Ashby','https://en.wikipedia.org/wiki/Ashby_station_(BART)','https://www.bart.gov/stations/ashb',false,false,false,false,false,false,'1972-01-29'),
  ('MA','MCAR','MACAR','MacArthur','https://en.wikipedia.org/wiki/MacArthur_station_(BART)','https://www.bart.gov/stations/mcar',false,false,false,false,false,true,'1972-09-11'),
  ('19','19TH','19ST','19th Street Oakland','https://en.wikipedia.org/wiki/19th_Street_Oakland_station','https://www.bart.gov/stations/19th',false,false,false,false,false,NULL,'1972-09-11'),
  ('12','12TH','12ST','12th Street Oakland City Center','https://en.wikipedia.org/wiki/12th_Street_Oakland_City_Center_station','https://www.bart.gov/stations/12th',false,false,false,false,false,NULL,'1972-09-11'),
  ('OW','WOAK','W OAK','West Oakland','https://en.wikipedia.org/wiki/West_Oakland_station','https://www.bart.gov/stations/woak',false,false,false,false,false,false,'1974-09-16'),
  ('EM','EMBR','EMBAR','Embarcadero','https://en.wikipedia.org/wiki/Embarcadero_station','https://www.bart.gov/stations/embr',false, true, false, false, false, false,'1976-05-27'),
  ('MT','MONT','MONTG','Montgomery','https://en.wikipedia.org/wiki/Montgomery_Street_station','https://www.bart.gov/stations/mont',false, true, false, false, false, true,'1973-11-05'),
  ('PL','POWL','POWEL','Powell Street','https://en.wikipedia.org/wiki/Powell_Street_station','https://www.bart.gov/stations/powl', false, true, false, false, false, false,'1973-11-05'),
  ('CC','CIVC','CIVIC','Civic Center/UN Plaza','https://en.wikipedia.org/wiki/Civic_Center/UN_Plaza_station','https://www.bart.gov/stations/civc', false, true, false, false, false, false,'1973-11-05'),
  ('16','16TH','16ST','16th Street Mission','https://en.wikipedia.org/wiki/16th_Street_Mission_station','https://www.bart.gov/stations/16th', false, false, false, false, false, false,'1973-11-05'),
  ('24','24TH','24ST','24th Street Mission','https://en.wikipedia.org/wiki/24th_Street_Mission_station','https://www.bart.gov/stations/24th', false, false, false, false, false, true,'1973-11-05'),
  ('GP','GLEN','GLNPK','Glen Park','https://en.wikipedia.org/wiki/Glen_Park_station','https://www.bart.gov/stations/glen', false, false, false, false, false, false,'1973-11-05'),
  ('BP','BALB','BALPK','Balboa Park','https://en.wikipedia.org/wiki/Balboa_Park_station','http://www.bart.gov/stations/balb', false, false, false, false, false, false,'1973-11-05'),
  ('DC','DALY','DALY','Daly City','https://en.wikipedia.org/wiki/Daly_City_station','https://www.bart.gov/stations/daly', false, false, false, false, true, true,'1973-11-05'),
  ('CM','COLM','COLMA','Colma','https://en.wikipedia.org/wiki/Colma_station','https://www.bart.gov/stations/colm', false, false, false, false, false, false,'1996-02-24'),
  ('SS','SSAN','S SAN','South San Francisco','https://en.wikipedia.org/wiki/South_San_Francisco_station_(BART)','https://www.bart.gov/stations/ssan', false, false, false, false, false, false,'2003-06-22'),
  ('SB','SBRN','SBRN','San Bruno','https://en.wikipedia.org/wiki/San_Bruno_station_(BART)','https://www.bart.gov/stations/sbrn', false, false, false, false, false, true,'2003-06-22'),
  ('SO','SFIA','SFO','San Francisco International Airport','https://en.wikipedia.org/wiki/San_Francisco_International_Airport_station','https://www.bart.gov/stations/sfia', true, false, false, false, true, true,'2003-06-22'),
  ('MB','MLBR','MILL','Millbrae','https://en.wikipedia.org/wiki/Millbrae_station','https://www.bart.gov/stations/mlbr', false, false, true, false, true, true,'2003-06-22'),
  ('WP','PITT','BAY PT','Pittsburg/Bay Point','https://en.wikipedia.org/wiki/Pittsburg/Bay_Point_station','https://www.bart.gov/stations/pitt', false, false, false, false, true, true,'1996-12-07'),
  ('NC','NCON','N CNC','North Concord/Martinez','https://en.wikipedia.org/wiki/North_Concord/Martinez_station','https://www.bart.gov/stations/ncon', false, false, false, false, false, true,'1995-12-16'),
  ('CN','CONC','CONCD','Concord','https://en.wikipedia.org/wiki/Concord_station','https://www.bart.gov/stations/conc', false, false, false, false, false, true,'1973-05-21'),
  ('PH','PHIL','PHILL','Pleasant Hill/Contra Costa Centre','https://en.wikipedia.org/wiki/Pleasant_Hill/Contra_Costa_Centre_station','https://www.bart.gov/stations/phil', false, false, false, false, false, true,'1973-05-21'),
  ('WC','WCRK','W CRK','Walnut Creek','https://en.wikipedia.org/wiki/Walnut_Creek_station','https://www.bart.gov/stations/wcrk', false, false, false, false, false, true,'1973-05-21'),
  ('LF','LAFY','LAFAY','Lafayette','https://en.wikipedia.org/wiki/Lafayette_station_(BART)','https://www.bart.gov/stations/lafy', false, false, false, false, false, false,'1973-05-21'),
  ('OR','ORIN','ORNDA','Orinda','https://en.wikipedia.org/wiki/Orinda_station','https://www.bart.gov/stations/orin', false, false, false, false, false, false,'1973-05-21'),
  ('RR','ROCK','ROCKR','Rockridge','https://en.wikipedia.org/wiki/Rockridge_station','https://www.bart.gov/stations/rock', false, false, false, false, false, false,'1973-05-21'),
  ('LM','LAKE','LAKEM','Lake Merritt','https://en.wikipedia.org/wiki/Lake_Merritt_station','https://www.bart.gov/stations/lake', false, false, false, false, false, false,'1972-09-11'),
  ('FV','FTVL','FRTVL','Fruitvale','https://en.wikipedia.org/wiki/Fruitvale_station','https://www.bart.gov/stations/ftvl', false, false, false, false, false, true,'1972-09-11'),
  ('CL','COLS','COLIS','Coliseum','https://en.wikipedia.org/wiki/Oakland_Coliseum_station','https://www.bart.gov/stations/cols', false, false, false, false, false, false,'1972-09-11'),
  ('SL','SANL','SLEAN','San Leandro','https://en.wikipedia.org/wiki/San_Leandro_station','https://www.bart.gov/stations/sanl', false, false, false, false, false, false,'1972-09-11'),
  ('BF','BAYF','BFAIR','Bay Fair','https://en.wikipedia.org/wiki/Bay_Fair_station','https://www.bart.gov/stations/bayf', false, false, false, false, false, true,'1972-09-11'),
  ('HY','HAYW','HAY','Hayward','https://en.wikipedia.org/wiki/Hayward_station_(BART)','https://www.bart.gov/stations/hayw', false, false, false, false, false, false,'1972-09-11'),
  ('SH','SHAY','SHAY','South Hayward','https://en.wikipedia.org/wiki/South_Hayward_station','https://www.bart.gov/stations/shay', false, false, false, false, false, false,'1972-09-11'),
  ('UC','UCTY','UCITY','Union City','https://en.wikipedia.org/wiki/Union_City_station','https://www.bart.gov/stations/ucty', false, false, false, false, false, false,'1972-09-11'),
  ('FM','FRMT','FREMT','Fremont','https://en.wikipedia.org/wiki/Fremont_station_(BART)','https://www.bart.gov/stations/frmt', false, false, false, false, true, true,'1972-09-11'),
  ('WS','WARM','WMSPR','Warm Springs/South Fremont','https://en.wikipedia.org/wiki/Warm_Springs/South_Fremont_station','https://www.bart.gov/stations/warm', false, false, false, false, true, true,'2017-03-25'),
  ('OA','OAKL','OAKL','Oakland International Airport','https://en.wikipedia.org/wiki/Oakland_International_Airport_station','https://www.bart.gov/stations/oakl', true, false, false, false, true, true,'2014-11-22'),
  ('CV','CAST','C VLY','Castro Valley','https://en.wikipedia.org/wiki/Castro_Valley_station','https://www.bart.gov/stations/cast', false, false, false, false, false, false,'1007-05-10'),
  ('WD','WDUB','W DUB','West Dublin/Pleasanton','https://en.wikipedia.org/wiki/West_Dublin/Pleasanton_(BART_station)','https://www.bart.gov/stations/wdub', false, false, false, false, false, false,'2011-02-19'),
  ('ED','DUBL','DUBLIN','Dublin/Pleasanton','https://en.wikipedia.org/wiki/Dublin/Pleasanton_station','https://www.bart.gov/stations/dubl', false, false, false, false, true, true, '1997-05-10');
