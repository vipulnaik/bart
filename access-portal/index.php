<?php
print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
print '<title>BART: Historical ridership, route, and price data</title>';
include_once('analytics.inc');
include_once("backend/globalVariables/passwordFile.inc");
include_once("backend/globalVariables/globalVariables.inc");
print '<link href="style.css" rel="stylesheet" type="text/css" />'."\n";
print '<script type="text/javascript" src="./jquery-3.1.1.min.js"></script>'."\n";
print '<script type="text/javascript" src="./jquery.tablesorter.js"></script>'."\n";
print '</head>';
print '<body>';
print '<script>$(document).ready(function()
    {
    }
); </script>'."\n";
include_once('preamble.inc');
print "<h4>Ridership, fare and route data between your chosen pair of stations</h4>\n";
print '<form method="post" action="ridership.php">'."\n";
print "<table>\n";
print "    <tr>\n";
print "      <td>Entry station (station 1)</td>\n";
$stationVariableName = "entryStation";
include("backend/stationDropdown.inc");
print "    </tr>\n";
print "    <tr>\n";
print "    <td>Exit station (station 2)</td>\n";
$stationVariableName = "exitStation";
include("backend/stationDropdown.inc");
print "    <tr>\n";
print '      <td><input type="submit" value="Submit"></td>'."\n";
print "    </tr>\n";
print "</table>\n";
print "</form>\n";
print "<h4>Station data for a single station, including fares, time, and ridership to all other stations in a given month</h4>\n";
print '<form method="post" action="station.php">';
print "<table>\n";
print "    <tr>\n";
print "      <td>Station for which you want the information dump</td>\n";
$stationVariableName = "station";
include("backend/stationDropdown.inc");
print "    </tr>\n";
print "    <tr>\n";
print "      <td>Month for which to show ridership data</td>\n";
$monthVariableName = "month";
include("backend/monthDropdown.inc");
print "    </tr>\n";
print "    <tr>\n";
print '      <td><input type="submit" value="Submit"></td>'."\n";
print "    </tr>\n";
print "</table>\n";
print "</form>\n";
print "</body>\n";
?>
