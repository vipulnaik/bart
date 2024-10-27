<?php
include_once('doctype.inc');
print '<script src="change-theme.js"></script>';
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
include_once("backend/backendQueries.inc");
include_once("backend/displayFunctions.inc");
$permalinkUrl = "https://bart.vipulnaik.com/station.php?station=$station&month=$month";
print "<p>Permalink URL: <a href=\"$permalinkUrl\">$permalinkUrl</a></p>";
function notTotal($stationName) {
  return ($stationName != "total");
}
printStationData(array_filter(array($station),"notTotal"));
printRidershipOneMonth($station, $month);

include_once('anchorjs.inc');
print '</body>';
?>
