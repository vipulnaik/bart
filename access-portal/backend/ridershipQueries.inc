<?php

function getRidership($entryStation, $exitStation) {
  global $mysqli;
  $ridershipQuery = "";
  if ($entryStation == "total" and $exitStation == "total") {
    $ridershipQuery = "select monthfull, day_type, ridercount from ridership_total;";
  } else if ($exitStation == "total") {
    $ridershipQuery = "select monthfull, day_type, ridercount from ridership_entry_total where entry_station_code='$entryStation';";
  } else if ($entryStation == "total") {
    $ridershipQuery = "select monthfull, day_type, ridercount from ridership_exit_total where exit_station_code='$exitStation';";
  } else {
    $ridershipQuery = "select * from ridership where entry_station_code='$entryStation' and exit_station_code='$exitStation';";
  }
  # print "$ridershipQuery\n";
  $ridershipResult = $mysqli -> query($ridershipQuery);
  # print "Number of rows in response: ".($ridershipResult -> num_rows)."\n";
  for ($i = 0; $i < $ridershipResult -> num_rows; $i++) {
    $ridershipRow = $ridershipResult -> fetch_assoc();
    $monthfull = $ridershipRow['monthfull'];
    $dayType = $ridershipRow['day_type'];
    $riderCount = $ridershipRow['ridercount'];
    $ridership[$monthfull][$dayType] = $riderCount;
  }
  return $ridership;
}

?>
