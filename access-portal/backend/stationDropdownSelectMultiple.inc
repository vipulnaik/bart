<?php

print '<td><select multiple name="'.$multipleStationVariableName.'[]" size="10">';
$query = "select * from stations order by ordinary_name;";
$result = $mysqli -> query($query);
print "<option value=\"total\"";
if (($multipleStationVariableName == "entryStationsList" and isset($entryStationsList) and in_array("total", $entryStationsList)) or ($multipleStationVariableName == "exitStationsList" and isset($exitStationsList) and in_array("total", $exitStationsList)) or ($multipleStationVariableName == "stationsList" and isset($stationsList) and in_array("total",$stationsList))) {
  print ' selected';
}
print ">Total across all stations</option>\n";
for($i=0; $i < $result -> num_rows; $i++) {
  $row = $result -> fetch_assoc();
  print "<option value=\"".$row['code_2l']."\"";
  if (($multipleStationVariableName == "entryStationsList" and isset($entryStationsList) and in_array($row['code_2l'], $entryStationsList)) or ($multipleStationVariableName == "exitStationsList" and isset($exitStationsList) and in_array($row['code_2l'], $exitStationsList)) or ($multipleStationVariableName == "stationsList" and isset($stationsList) and in_array($row['code_2l'],$stationsList))) {
    print ' selected';
  }
  print ">".$row['ordinary_name']." (".$row['code_2l'].";".$row['code_4l'].";".$row['code_long'].")</option>\n";
}
print "</select>\n";
print "</td>\n";
?>
