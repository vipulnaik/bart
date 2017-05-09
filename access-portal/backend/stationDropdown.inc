<?php

print '<td><select name="'.$stationVariableName.'">';
$query = "select * from stations order by ordinary_name;";
$result = $mysqli -> query($query);
for($i=0; $i < $result -> num_rows; $i++) {
  $row = $result -> fetch_assoc();
  print "<option value=\"".$row['code_2l']."\" ";
  print ">".$row['ordinary_name']." (".$row['code_2l'].";".$row['code_4l'].";".$row['code_long'].")</option>";
}
print "</select></td></tr>";
?>