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
        if ($timeDiff > 0) {
          $routeAndTime['time'] = $timeDiff;
          $routeAndTime['start'] = $routeResultRow['end_station_code'];
          $routeAndTime['end'] = $routeResultRow['start_station_code'];
          array_push($routesAndTimes, $routeAndTime);
        } else {
          $routeAndTime['time'] = -$timeDiff;
          $routeAndTime['start'] =  $routeResultRow['start_station_code'];
          $routeAndTime['end'] = $routeResultRow['end_station_code'];
          array_push($routesAndTimes, $routeAndTime);
        }
      } else {
        # print "Row $i does not qualify because time1 ".$routeResultRow['time1']." or time2 ".$routeResultRow['time2']." is -1";
      }
    }
    return $routesAndTimes;
  }
}

function getRoutesAndTimesIndirect($entryStation, $exitStation) {
  global $mysqli;
  global $transferStations;
  $routesAndTimesPairs = array();
  $minTimeSoFar = 120;
  foreach ($transferStations as $transferStation) {
    # print("<p>Computing routes between entryStation $entryStation and exitStation $exitStation via transferStation $transferStation</p>\n");
    $routesAndTimesLeg1 = getRoutesAndTimes($entryStation, $transferStation);
    $routesAndTimesLeg2 = getRoutesAndTimes($transferStation, $exitStation);
    if (count($routesAndTimesLeg1) > 0 and count($routesAndTimesLeg2) > 0) {
      $routesAndTimesPair['transferStation'] = $transferStation;
      $routesAndTimesPair['leg1'] = $routesAndTimesLeg1;
      $routesAndTimesPair['leg2'] = $routesAndTimesLeg2;
      $timeForThisJourney = $routesAndTimesPair['leg1'][0]['time'] + $routesAndTimesPair['leg2'][0]['time'];
      # print("<p>Time for journey via transferStation $transferStation is $timeForThisJourney</p>\n");
      if ($timeForThisJourney >= $minTimeSoFar and $timeForThisJourney <= $minTimeSoFar + 3) {
        # print("<p>Journey via transferStation $transferStation is as efficient or slightly more inefficient than optimal journey so far, seen by comparing timeForThisJourney $timeForThisJourney against minTimeSoFar $minTimeSoFar</p>\n");
        array_push($routesAndTimesPairs, $routesAndTimesPair);
      } else if ($timeForThisJourney < $minTimeSoFar - 3) {
        # print ("<p>Journey via transferStation $transferStation is much more efficient than optimal journey so far, seen by comparing timeForThisJourney $timeForThisJourney against minTimeSoFar $minTimeSoFar</p>\n");
        $routesAndTimesPairs = array($routesAndTimesPair);
        $minTimeSoFar = $timeForThisJourney + 0;
        # print("<p>minTimeSoFar = $minTimeSoFar</p>\n");
      } else if ($timeForThisJourney < $minTimeSoFar) {
        # print ("<p>Journey via transferStation $transferStation is slightly but not much more efficient than optimal journey so far, seen by comparing timeForThisJourney $timeForThisJouney against minTimeSoFar $minTimeSoFar</p>\n");
        $minTimeSoFar = $timeForThisJourney + 0;
        # print("<p>minTimeSoFar = $minTimeSoFar</p>\n");
        array_push($routesAndTimesPairs, $routesAndTimesPair);
      }
    }
  }
  return $routesAndTimesPairs;
}

function getStationName($code_2l) {
  global $mysqli;
  $nameQuery = "select ordinary_name from stations where code_2l = '$code_2l';";
  $nameResult = $mysqli -> query($nameQuery);
  if ($nameResult -> num_rows > 0) {
    $nameRow = $nameResult -> fetch_assoc();
    return $nameRow['ordinary_name'];
  }
}

function getRoutesBeforeOrAfter($start_station_code, $end_station_code, $station_code, $time_from_start, $beforeOrAfter = 'before') {
  global $mysqli;
  $symbol = "<=";
  if (beforeOrAfter == "after") {
    $symbol = ">";
  }
  $stationsQuery = "select station_code, time_from_start from routes where start_station_code='$start_station_code' and end_station_code='$end_station_code' and $station_code != '$station_code' and time_from_start $symbol $time_from_start";
  $stationsResult = $mysqli -> query($stationsQuery);
  $stationList = array();
  for($i = 0; $i < $stationsResult -> num_rows; $i++) {
    $stationsRow = $stationsResult -> fetch_assoc();
    array_push($stationList, $stationsRow);
  }
  return $stationList;
}

function getSortedRoutesList($station_code) {
  global $mysqli;
  $routesQuery = "select start_station_code, end_Station_code, time_from_start from routes where station_code='$station_code';";
  $routesResult = $mysqli -> query ($routesQuery);
  $stationArray = array();
  for ($i=0;$i < $routesResult -> num_rows; $i++) {
    $routesResultRow = $routesResult -> fetch_assoc();
    $start_station_code = $routesResultRow['start_station_code'];
    $end_station_code = $routesResultRow['end_station_code'];
    $time_from_start = $routesResultRow['time_from_start'];
  }
}

?>
