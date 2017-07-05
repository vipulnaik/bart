<?php
$query = "select distinct monthfull from ridership";
$result = $mysqli -> query($query);
$monthListOriginal = array();
for ($i = 0; $i < $result -> num_rows; $i++) {
  $row = $result -> fetch_assoc();
  array_push($monthListOriginal, $row['monthfull']);
}
sort($monthListOriginal);
$monthList = array_reverse($monthListOriginal);
$excursionFare = 5.75;
$transferStations = array('MA','BF','BP','SB','19','12','OW');
?>
