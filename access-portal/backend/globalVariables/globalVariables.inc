<?php
$query = "select distinct monthfull from ridership order by monthfull desc";
$result = $mysqli -> query($query);
$monthList = array();
for ($i = 0; $i < $result -> num_rows; $i++) {
  $row = $result -> fetch_assoc();
  array_push($monthList, $row['monthfull']);
}
?>
