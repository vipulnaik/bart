<?php
include_once('doctype.inc');
print '<script src="change-theme.js"></script>';
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
include_once('style.inc');
print '<script type="text/javascript" src="./jquery-3.7.1.min.js"></script>'."\n";
print '<script type="text/javascript" src="./jquery.tablesorter.js"></script>'."\n";
print '</head>';
print '<body>';
print '<script>$(document).ready(function()
    {
        $("#ridershipData").tablesorter();
    }
); </script>'."\n";
?>

<p><span id="changeThemeMenu" style="display: none;">Set color scheme to:
         <span id="auto-menu-option" style="cursor: pointer;" class="unselectable" onclick="change_theme.set_color('auto')">auto</span>,
         <span id="light-menu-option" style="cursor: pointer;" class="unselectable" onclick="change_theme.set_color('light')">light</span>,
         <span id="dark-menu-option" style="cursor: pointer;" class="unselectable" onclick="change_theme.set_color('dark')">dark</span>
</span>&thinsp;<!-- blank space to prevent cumulative layout shift --></p>
<script>change_theme.set_theme_from_local_storage();</script>

<?php
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

include_once('anchorjs.inc');
print '</body>';
?>
