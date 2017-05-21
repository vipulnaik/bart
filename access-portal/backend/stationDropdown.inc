<?php

print '<td><select name="'.$stationVariableName.'">';
$query = "select * from stations order by ordinary_name;";
$result = $mysqli -> query($query);
print "<option value=\"total\"";
if (($stationVariableName == "entryStation" and $row['code_2l'] == "total") or ($stationVariableName == "exitStation" and $row['code_2l'] == "total")) {
  print ' selected';
}
print ">Total across all stations</option>\n";
for($i=0; $i < $result -> num_rows; $i++) {
  $row = $result -> fetch_assoc();
  print "<option value=\"".$row['code_2l']."\" ";
  if (($stationVariableName == "entryStation" and $row['code_2l'] == $entryStation) or ($stationVariableName == "exitStation" and $row['code_2l'] == $exitStation)) {
    print ' selected';
  }
  print ">".$row['ordinary_name']." (".$row['code_2l'].";".$row['code_4l'].";".$row['code_long'].")</option>\n";
}
print "</select></td></tr>";
?>