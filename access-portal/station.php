<?php
print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
$station = '12';
if (!empty($_REQUEST['station'])) {
  $station = $_REQUEST['station'];
}
$month = '2017-04';
if (!empty($_REQUEST['month'])) {
  $month = $_REQUEST['month'];
}

print "<title>BART $station Station Data</title>";
include_once("analytics.inc");
include_once("backend/globalVariables/passwordFile.inc");
include_once("backend/globalVariables/globalVariables.inc");
print '<link href="style.css" rel="stylesheet" type="text/css" />'."\n";
print '<script type="text/javascript" src="./jquery-3.1.1.min.js"></script>'."\n";
print '<script type="text/javascript" src="./jquery.tablesorter.js"></script>'."\n";
print '</head>';
print '<body>';
print '<script>$(document).ready(function()
    {
        $("#ridershipData").tablesorter();
    }
); </script>'."\n";
include_once('preamble.inc');
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
include_once("backend/backendQueries.inc");
include_once("backend/displayFunctions.inc");
$permalinkUrl = "https://bart.vipulnaik.com/station.php?station=$station&month=$month";
print "<p>Permalink URL: <a href=\"$permalinkUrl\">$permalinkUrl</a></p>";
function notTotal($stationName) {
  return ($stationName != "total");
}
printStationData(array_filter(array($station),"notTotal"));
print '</body>';
?>
