<?php
print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html lang="en-US"><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
$entryStationsList = array();
if (!empty($_REQUEST['entryStationsList'])) {
  $entryStationsList = $_REQUEST['entryStationsList'];
}
$exitStationsList = array();
if (!empty($_REQUEST['exitStationsList'])) {
  $exitStationsList = $_REQUEST['exitStationsList'];
}

$entryStationsListString = join(",", $entryStationsList);
$exitStationsListString = join(",", $exitStationsList);

print "<title>BART Ridership: $entryStationsListString to $exitStationsListString</title>";
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

# print "entryStationsListString = $entryStationsListString";
# print "exitStationsListString = $exitStationsListString";

# Form
print '<form method="get" action="ridership-multiple.php">'."\n";
print "<table>\n";
print "    <tr>\n";
print "      <td>Entry stations list</td>\n";
$multipleStationVariableName = "entryStationsList";
include("backend/stationDropdownSelectMultiple.inc");
print "    </tr>\n";
print "    <tr>\n";
print "    <td>Exit stations list</td>\n";
$multipleStationVariableName = "exitStationsList";
include("backend/stationDropdownSelectMultiple.inc");
print "    <tr>\n";
print '      <td><input type="submit" value="Submit"></td>'."\n";
print "    </tr>\n";
print "</table>\n";
print "</form>\n";
print "</body>\n";

include_once("backend/backendQueries.inc");
include_once("backend/displayFunctions.inc");
function notTotal($stationName) {
  return ($stationName != "total");
}
printListRidership($entryStationsList, $exitStationsList);
print '</body>';
?>
