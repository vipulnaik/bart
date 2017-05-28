<?php

function getFaresAndEffectiveDates($entryStation, $exitStation) {
  global $mysqli;
  $fareQuery = "select fare, effective_date from fares where start_station_code = '$entryStation' and end_station_code = '$exitStation' or start_station_code = '$exitStation' and end_station_code = '$entryStation' order by effective_date desc;";
  # print("Fare query: $fareQuery");
  $fareRows = array();
  $fareResult = $mysqli -> query($fareQuery);
  for ($i=0;$i < $fareResult -> num_rows; $i++) {
    $fareResultRow = $fareResult -> fetch_assoc();
    array_push($fareRows, $fareResultRow);
  }
  return $fareRows;
}

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

function getRoutesAndTimes($entryStation, $exitStation) {
  global $mysqli;
  # print "Entered getRoutesAndTimes with entryStation = $entryStation and exitStation = $exitStation<br/>\n";  
  if ($entryStation == $exitStation) {
    # print "$entryStation == $exitStation, so punting";
    $routeAndTime['time'] = 0;
    $routeAndTime['start'] = "N/A";
    $routeAndTime['end'] = "N/A";
    $routesAndTimes = array($routeAndTime);
    return $routesAndTimes;
  } else {
    $routeQuery = "select start_station_code, end_station_code, sum(case when station_code = '$entryStation' then time_from_start else case when start_station_code = '$entryStation' then 0 else -1 end end) as time1, sum(case when station_code = '$exitStation' then time_from_start else case when start_station_code = '$exitStation' then 0 else -1 end end) as time2 from routes where station_code in ('$entryStation', '$exitStation') or start_station_code in ('$entryStation','$exitStation') group by start_station_code, end_station_code;";
    # print "Running routeQuery = $routeQuery";
    $routeResult = $mysqli -> query($routeQuery);
    $routesAndTimes = array();
    for ($i = 0; $i < $routeResult -> num_rows; $i++) {
      # print "Looking at row $i of result\n";
      $routeResultRow = $routeResult -> fetch_assoc();
      if ($routeResultRow['time1'] > -1 and $routeResultRow['time2'] > -1) {
        $timeDiff = $routeResultRow['time1'] - $routeResultRow['time2'];
        # print "timeDiff $timeDiff is obtained as ".$routeResultRow['time1']." - ".$routeResultRow['time2']."<br/>\n";
	$startStationResult = $mysqli -> query("select ordinary_name from stations where code_2l = '".$routeResultRow['start_station_code']."';");
        $startStationRow = $startStationResult -> fetch_assoc();
        $startStation = $startStationRow['ordinary_name'];
	$endStationResult = $mysqli -> query("select ordinary_name from stations where code_2l = '".$routeResultRow['end_station_code']."';");
        $endStationRow = $endStationResult -> fetch_assoc();
        $endStation = $endStationRow['ordinary_name'];
        if ($timeDiff > 0) {
          $routeAndTime['time'] = $timeDiff;
          $routeAndTime['start'] = $endStation;
          $routeAndTime['end'] = $startStation;
          array_push($routesAndTimes, $routeAndTime);
        } else {
          $routeAndTime['time'] = -$timeDiff;
          $routeAndTime['start'] =  $startStation;
          $routeAndTime['end'] = $endStation;
          array_push($routesAndTimes, $routeAndTime);
        }
      } else {
        # print "Row $i does not qualify because time1 ".$routeResultRow['time1']." or time2 ".$routeResultRow['time2']." is -1";
      }
    }
    return $routesAndTimes;
  }
}
?>
