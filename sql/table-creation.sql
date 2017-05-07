create table ridership(
  ridership_id int(11) not null auto_increment primary key, 
  monthfull varchar(7) not null,
  day_type enum('weekday','saturday','sunday'),
  entry_station_code varchar(2) not null,
  exit_station_code varchar(2) not null,
  count int(11) not null,
  unique mtee(monthfull, day_type, entry_station_code, exit_station_code)
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

create table stations(
  code_2l varchar(2) not null,
  code_long varchar(6) not null,
  ordinary_name varchar(100) not null,
  wikipedia_page varchar(100) not null,
  bart_page varchar(100) not null,
  airport boolean default false, 
  muni_connection boolean default false,
  caltrain_connection boolean default false,
  amtrak_connection boolean default false,
  end_of_line boolean default false,
  trains_can_turn boolean
) ENGINE=InnoDB AUTO_INCREMENT=15239276 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

insert into stations(code_2l, code_long, ordinary_name, wikipedia_page, bart_page, airport, muni_connection, caltrain_connection, amtrak_connection, end_of_line, train_can_turn)  values
  ('RM','RICH','Richmond','https://en.wikipedia.org/wiki/Richmond_station_(California)','https://www.bart.gov/stations/rich',false,false,false,true,true,true),
  ('EN','DEL N','El Cerrito del Norte','https://en.wikipedia.org/wiki/El_Cerrito_del_Norte_(BART_station)','https://www.bart.gov/stations/deln',false,false,false,false,false,NULL),
  ('EP','PLAZA','El Cerrito Plaza','https://en.wikipedia.org/wiki/El_Cerrito_Plaza_station','https://www.bart.gov/stations/plza',false,false,false,false,false,NULL),
  ('NB','N BRK','North Berkeley','https://en.wikipedia.org/wiki/North_Berkeley_station','https://www.bart.gov/stations/nbrk',false,false,false,false,false,false),
  ('BK','BRK','Downtown Berkeley','https://en.wikipedia.org/wiki/Downtown_Berkeley_station','https://www.bart.gov/stations/dbrk',false,false,false,false,false,false),
  ('AS','ASHBY','Ashby','https://en.wikipedia.org/wiki/Ashby_station_(BART)','https://www.bart.gov/stations/ashb',false,false,false,false,false,false),
  ('MA','MACAR','MacArthur','https://en.wikipedia.org/wiki/MacArthur_station_(BART)','https://www.bart.gov/stations/mcar',false,false,false,false,false,true),
  ('19','19ST','19th Street Oakland','https://en.wikipedia.org/wiki/19th_Street_Oakland_station','https://www.bart.gov/stations/19th',false,false,false,false,false,NULL),
  ('12','12ST','12th Street Oakland City Center','https://en.wikipedia.org/wiki/12th_Street_Oakland_City_Center_station','https://www.bart.gov/stations/12th',false,false,false,false,false,NULL),
  ('OW','W OAK','West Oakland','https://en.wikipedia.org/wiki/West_Oakland_station','https://www.bart.gov/stations/woak',false,false,false,false,false,false);
  ('EM','EMBAR','Embarcadero','https://en.wikipedia.org/wiki/Embarcadero_station','https://www.bart.gov/stations/embr',false, true, false, false, false, false),
  ('MT','MONTG','Montgomery','https://en.wikipedia.org/wiki/Montgomery_Street_station','https://www.bart.gov/stations/mont',false, true, false, false, false, true),
  ('PL','POWEL','Powell Street','https://en.wikipedia.org/wiki/Powell_Street_station','https://www.bart.gov/stations/powl', false, true, false, false, false, false),
  ('CC','CIVIC','Civic Center/UN Plaza','https://en.wikipedia.org/wiki/Civic_Center/UN_Plaza_station','https://www.bart.gov/stations/civc', false, true, false, false, false, false),
  ('16','16ST','16th Street Mission','https://en.wikipedia.org/wiki/16th_Street_Mission_station','https://www.bart.gov/stations/16th', false, false, false, false, false, false),
  ('24','24ST','24th Street Mission','https://en.wikipedia.org/wiki/24th_Street_Mission_station','https://www.bart.gov/stations/24th', false, false, false, false, false, true),
  ('GP','GLNPK','Glen Park','https://en.wikipedia.org/wiki/Glen_Park_station','https://www.bart.gov/stations/glen', false, false, false, false, false, false),
  ('BP','BALPK','Balboa Park','https://en.wikipedia.org/wiki/Balboa_Park_station','http://www.bart.gov/stations/balb', false, false, false, false, false, false, false),
  ('DC','DALY','Daly City','https://en.wikipedia.org/wiki/Daly_City_station','https://www.bart.gov/stations/daly', false, false, false, false, true, true),
  ('CM','COLMA','Colma','https://en.wikipedia.org/wiki/Colma_station','https://www.bart.gov/stations/colm', false, false, false, false, false, false),
  ('SS','S SAN','South San Francisco','https://en.wikipedia.org/wiki/South_San_Francisco_station_(BART)','https://www.bart.gov/stations/ssan', false, false, false, false, false, false),
  ('SB','SBRN','San Bruno','https://en.wikipedia.org/wiki/San_Bruno_station_(BART)','https://www.bart.gov/stations/sbrn', false, false, false, false, false, true),
  ('SO','SFO','San Francisco International Airport','https://en.wikipedia.org/wiki/San_Francisco_International_Airport_station','https://www.bart.gov/stations/sfia', true, false, false, false, true, true),
  ('MB','MILL','Millbrae','https://en.wikipedia.org/wiki/Millbrae_station','https://www.bart.gov/stations/mlbr', false, false, true, false, true, true),
  ('BP','BAY PT','Pittsburg/Bay Point','https://en.wikipedia.org/wiki/Pittsburg/Bay_Point_station','https://www.bart.gov/stations/pitt', false, false, false, false, true, true),
  ('NC','N CNC','North Concord/Martinez','https://en.wikipedia.org/wiki/North_Concord/Martinez_station','https://www.bart.gov/stations/ncon', false, false, false, false, false, true),
  ('CN','CONCD','Concord','https://en.wikipedia.org/wiki/Concord_station','https://www.bart.gov/stations/conc', false, false, false, false, false, true),
  ('PH','PHILL','Pleasant Hill/Contra Costa Centre','https://en.wikipedia.org/wiki/Pleasant_Hill/Contra_Costa_Centre_station','https://www.bart.gov/stations/phil', false, false, false, false, false, true),
  ('WC','W CRK','Walnut Creek','https://en.wikipedia.org/wiki/Walnut_Creek_station','https://www.bart.gov/stations/wcrk', false, false, false, false, false, true),
  ('LF','LAFAY','Lafayette','https://en.wikipedia.org/wiki/Lafayette_station_(BART)','https://www.bart.gov/stations/lafy', false, false, false, false, false, false),
  ('OR','ORNDA','Orinda','https://en.wikipedia.org/wiki/Orinda_station','https://www.bart.gov/stations/orin', false, false, false, false, false, false),
  ('RR','ROCKR','Rockridge','https://en.wikipedia.org/wiki/Rockridge_station','https://www.bart.gov/stations/rock', false, false, false, false, false, false),
  ('LM','LAKEM','Lake Merritt','https://en.wikipedia.org/wiki/Lake_Merritt_station','https://www.bart.gov/stations/lake', false, false, false, false, false, false),
  ('FV','FRTVL','Fruitvale','https://en.wikipedia.org/wiki/Fruitvale_station','https://www.bart.gov/stations/ftvl', false, false, false, false, false, true);

