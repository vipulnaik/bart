Sometime on the 3rd or later of a new month:

1. Go to https://www.bart.gov/about/reports/ridership, click to the
   link for the current year, then see if the most recent completed
   month's data is there.

2. Open the xlsx file in Numbers.

3. Export to CSV.

4. Move the CSV files to `ridershop/<yyyy-mm>` and rename them to
   weekday.csv, saturday.csv, sunday.csv and (if applicable) total.csv.

5. Update [station-code-reader.scala](station-code-reader.scala) to
   include the most recent completed month, then run the code.

6. Stage and commit changes to GitHub.

7. Run `truncate table ridership` in MySQL (after switching to the
   database) and then run `mysql bart -p < ridership/insertions.sql`.

8. Run the following to regenerate summaries:

```
truncate table ridership_entry_total; insert into ridership_entry_total(monthfull, entry_station_code, day_type, ridercount) select monthfull, entry_station_code, day_type, sum(ridercount) from ridership group by monthfull, entry_station_code, day_type; truncate table ridership_exit_total; insert into ridership_exit_total(monthfull, exit_station_code, day_type, ridercount) select monthfull, exit_station_code, day_type, sum(ridercount) from ridership group by monthfull, exit_station_code, day_type; truncate table ridership_total; insert into ridership_total(monthfull, day_type, ridercount) select monthfull, day_type, sum(ridercount) from ridership group by monthfull, day_type;
```

9. Verify on bart.vipulnaik.com that the charts and data now include
   the most recent completed month.
