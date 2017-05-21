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
$stationVariableName = "entryStation";
print '<form method="post" action="ridership.php">';
print '<table>';
print '<tr>';
print '<td>Entry station (station 1)</td>';
include("backend/stationDropdown.inc");
print '</tr>';
print '<tr>';
print '<td>Exit station (station 2)</td>';
$stationVariableName = "exitStation";
include("backend/stationDropdown.inc");
print '<tr><td><input type="submit" value="Submit"></td>';
print '</tr>';
print '</table>';
print '</form>';
print '</body>';
?>
