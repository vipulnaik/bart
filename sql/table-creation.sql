create table stations(
  code_2l varchar(2) not null,
  code_long varchar(5) not null,
  ordinary_name varchar(100) not null,
  wikipedia_page varchar(100) not null,
  caltrain_connection boolean default false,
  amtrak_connection boolean default false,
  end_of_line boolean default false,
  trains_can_turn boolean
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

insert into stations values
  ('RM','RICH','Richmond','https://en.wikipedia.org/wiki/Richmond_station_(California)',false,true,true,true),
  ('EN','DEL N','El Cerrito del Norte','https://en.wikipedia.org/wiki/El_Cerrito_del_Norte_(BART_station)',false,false,false,NULL),
  ('EP','PLAZA','El Cerrito Plaza','https://en.wikipedia.org/wiki/El_Cerrito_Plaza_station',false,false,false,NULL),
  ('NB','N BRK','North Berkeley','https://en.wikipedia.org/wiki/North_Berkeley_station',false,false,false,false),
  ('BK','BRK','Downtown Berkeley','https://en.wikipedia.org/wiki/Downtown_Berkeley_station',false,false,false,false),
  ('AS','ASHBY','Ashby','https://en.wikipedia.org/wiki/Ashby_station_(BART)',false,false,false,false),
  ('MA','MACAR','MacArthur','https://en.wikipedia.org/wiki/MacArthur_station_(BART)',false,false,false,true),
  ('19','19ST','19th Street Oakland','https://en.wikipedia.org/wiki/19th_Street_Oakland_station',false,false,false,NULL),
  ('12','12ST','12th Street Oakland City Center','https://en.wikipedia.org/wiki/12th_Street_Oakland_City_Center_station',false,false,false,NULL),
  ('OW','W OAK','West Oakland','https://en.wikipedia.org/wiki/West_Oakland_station',false,false,false,false);
