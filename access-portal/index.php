<?php
include_once('doctype.inc');
print '<script src="change-theme.js"></script>';
print '<title>BART: Historical ridership, route, and price data</title>';
include_once('analytics.inc');
include_once("backend/globalVariables/passwordFile.inc");
include_once("backend/globalVariables/globalVariables.inc");
print '<link href="style.css" rel="stylesheet" type="text/css" />'."\n";
include_once('style.inc');
# The resources below are currently not needed on the home page
# print '<script type="text/javascript" src="./jquery-3.7.1.min.js"></script>'."\n";
# print '<script type="text/javascript" src="./jquery.tablesorter.js"></script>'."\n";
print '</head>';
print '<body>';
# print '<script>$(document).ready(function()
#     {
#     }
# ); </script>'."\n";
?>

<p><span id="changeThemeMenu" style="display: none;">Set color scheme to:
         <span id="auto-menu-option" style="cursor: pointer;" class="unselectable" onclick="change_theme.set_color('auto')">auto</span>,
         <span id="light-menu-option" style="cursor: pointer;" class="unselectable" onclick="change_theme.set_color('light')">light</span>,
         <span id="dark-menu-option" style="cursor: pointer;" class="unselectable" onclick="change_theme.set_color('dark')">dark</span>
</span>&thinsp;<!-- blank space to prevent cumulative layout shift --></p>
<script>change_theme.set_theme_from_local_storage();</script>

<?php
include_once('preamble.inc');
# Single station both sides
print "<h4>Ridership, fare and route data between your chosen pair of stations</h4>\n";
print '<form method="get" action="ridership.php">'."\n";
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

# Single station, single month; data with every other station
print '<form method="get" action="station.php">';
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

# Multiple stations both sides
print "<h4>Ridership, fare and route data between your chosen lists of stations</h4>\n";
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

include_once('anchorjs.inc');
print "</body>\n";
?>
