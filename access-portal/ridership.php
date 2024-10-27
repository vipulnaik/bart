<?php
include_once('doctype.inc');
print '<script src="change-theme.js"></script>';
$entryStation = '12';
if (!empty($_REQUEST['entryStation'])) {
  $entryStation = $_REQUEST['entryStation'];
}
$exitStation = '12';
if (!empty($_REQUEST['exitStation'])) {
  $exitStation = $_REQUEST['exitStation'];
}

print "<title>BART Ridership: $entryStation to $exitStation</title>";
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
# Form
print '<form method="get" action="ridership.php">';
print '<table>';
print '<tr>';
print '<td>Entry station (station 1)</td>';
$stationVariableName = "entryStation";
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

include_once("backend/backendQueries.inc");
include_once("backend/displayFunctions.inc");
$permalinkUrl = "https://bart.vipulnaik.com/ridership.php?entryStation=$entryStation&exitStation=$exitStation";
print "<p>Permalink URL: <a href=\"$permalinkUrl\">$permalinkUrl</a></p>";
function notTotal($stationName) {
  return ($stationName != "total");
}
printStationData(array_filter(array($entryStation, $exitStation),"notTotal"));
printRoutesAndFares($entryStation, $exitStation);
printRidership($entryStation, $exitStation);

include_once('anchorjs.inc');
print '</body>';
?>
