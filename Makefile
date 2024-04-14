MYSQL_ARGS=
DATABASE=bart

.PHONY: init
init:
	mysql $(MYSQL_ARGS) -e "create database if not exists $(DATABASE);"
	mkdir -p access-portal/images

.PHONY: reset
reset:
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists fares;"
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists ridership;"
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists ridership_entry_total;"
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists ridership_exit_total;"
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists ridership_total;"
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists routes;"
	mysql $(MYSQL_ARGS) $(DATABASE) -e "drop table if exists stations;"

.PHONY: read_base
read_base:
	mysql $(MYSQL_ARGS) $(DATABASE) < sql/table_creation.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < sql/routes.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < sql/stations.sql

.PHONY: refresh_ridership
refresh_ridership:
	mysql $(MYSQL_ARGS) $(DATABASE) -e "truncate table ridership;"
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2001.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2002.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2003.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2004.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2005.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2006.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2007.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2008.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2009.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2010.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2011.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2012.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2013.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2014.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2015.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2016.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2017.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2018.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2019.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2020.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2021.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2022.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2023.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < ridership/insertions-2024.sql
	mysql $(MYSQL_ARGS) $(DATABASE) < sql/generate_summaries.sql

.PHONY: read
read: read_base refresh_ridership

.PHONY: fetch_table_sorting
fetch_table_sorting:
	curl -Lo access-portal/jquery-3.7.1.min.js \
		'https://code.jquery.com/jquery-3.7.1.min.js'
	curl -Lo access-portal/jquery.tablesorter.js \
		'https://github.com/christianbach/tablesorter/raw/master/jquery.tablesorter.js'
	curl -Lo access-portal/style.css \
		'https://raw.githubusercontent.com/christianbach/tablesorter/master/themes/blue/style.css'
	curl -Lo access-portal/bg.gif \
		'https://github.com/christianbach/tablesorter/raw/master/themes/blue/bg.gif'
	curl -Lo access-portal/asc.gif \
		'https://github.com/christianbach/tablesorter/raw/master/themes/blue/asc.gif'
	curl -Lo access-portal/desc.gif \
		'https://github.com/christianbach/tablesorter/raw/master/themes/blue/desc.gif'

.PHONY: clean_table_sorting
clean_table_sorting:
	rm -f access-portal/jquery-*.min.js
	rm -f access-portal/jquery.tablesorter.js
	rm -f access-portal/style.css
	rm -f access-portal/bg.gif
	rm -f access-portal/asc.gif
	rm -f access-portal/desc.gif

.PHONY: fetch_anchorjs
fetch_anchorjs:
	curl -Lo access-portal/anchor.min.js \
		'https://raw.githubusercontent.com/bryanbraun/anchorjs/master/anchor.min.js'

.PHONY: clean_anchorjs
clean_anchorjs:
	rm -f access-portal/anchor.min.js
