<?php

function getFaresAndEffectiveDates($entryStation, $exitStation) {
  global $mysqli;
  $fareQuery = "select fare, effective_date from fares where start_station_code = ? and end_station_code = ? or start_station_code = ? and end_station_code = ? order by effective_date desc;";
  $fareRows = array();
  $stmt = $mysqli -> prepare($fareQuery);
  $stmt -> bind_param("ssss", $entryStation, $exitStation, $exitStation, $entryStation);
  $stmt -> execute();
  $fareResult = $stmt -> get_result();
  for ($i=0;$i < $fareResult -> num_rows; $i++) {
    $fareResultRow = $fareResult -> fetch_assoc();
    array_push($fareRows, $fareResultRow);
  }
  return $fareRows;
}

function getApplicableFareForMonth($entryStation, $exitStation, $monthfull) {
  global $mysqli;
  $applicableFareQuery = "select fare from fares where (start_station_code = ? and end_station_code = ? or start_station_code = ? and end_station_code = ?) and effective_date <= '$monthfull"."-01' order by effective_date;";
  $stmt = $mysqli -> prepare($applicableFareQuery);
  $stmt -> bind_param("ssss", $entryStation, $exitStation, $exitStation, $entryStation);
  $stmt -> execute();
  $applicableFareResult = $stmt -> get_result();
  if ($applicableFareResult -> num_rows == 0) {
    return "N/A";
  } else {
    for ($i=0;$i < $applicableFareResult -> num_rows; $i++) {
      $applicableFareRow = $applicableFareResult -> fetch_assoc();
      $fare = $applicableFareRow['fare'];
    }
    return sprintf("%.2f",$fare);
  }
}

function questionMark($input) {
  return "?";
}
function stringAnnotation($input) {
  return "s";
}

function getRidership($entryStationsList, $exitStationsList) {
  global $mysqli;
  $ridershipQuery = "";
  $entryStationQuestionMarks = join(",", array_map("questionMark", $entryStationsList));
  $exitStationQuestionMarks = join(",", array_map("questionMark", $exitStationsList));
  $entryStationAnnotations = join("", array_map("stringAnnotation", $entryStationsList));
  $exitStationAnnotations = join("", array_map("stringAnnotation", $exitStationsList));
  if (in_array("total", $entryStationsList) and in_array("total", $exitStationsList)) {
    $ridershipQuery = "select monthfull, day_type, rider_count from ridership_total;";
  } else if (in_array("total", $exitStationsList)) {
    $ridershipQuery = "select monthfull, day_type, coalesce(sum(rider_count), 0) as rider_count from ridership_entry_total where entry_station_code in ($entryStationQuestionMarks) group by monthfull, day_type;";
  } else if (in_array("total", $entryStationsList)) {
    $ridershipQuery = "select monthfull, day_type, coalesce(sum(rider_count), 0) as rider_count from ridership_exit_total where exit_station_code in ($exitStationQuestionMarks) group by monthfull, day_type;";
  } else {
    $ridershipQuery = "select monthfull, day_type, coalesce(sum(rider_count), 0) as rider_count from ridership where entry_station_code in ($entryStationQuestionMarks) and exit_station_code in ($exitStationQuestionMarks) group by monthfull, day_type;";
  }
  $stmt = $mysqli -> prepare($ridershipQuery);
  if (in_array("total", $entryStationsList) and in_array("total", $exitStationsList)) {
    # do nothing
  } else if (in_array("total", $exitStationsList)) {
    $stmt -> bind_param($entryStationAnnotations, ...$entryStationsList);
  } else if (in_array("total", $entryStationsList)) {
    $stmt -> bind_param($exitStationAnnotations, ...$exitStationsList);
  } else {
    $stmt -> bind_param($entryStationAnnotations . $exitStationAnnotations, ...$entryStationsList, ...$exitStationsList);
  }
  $stmt -> execute();
  $ridershipResult = $stmt -> get_result();
  for ($i = 0; $i < $ridershipResult -> num_rows; $i++) {
    $ridershipRow = $ridershipResult -> fetch_assoc();
    $monthfull = $ridershipRow['monthfull'];
    $dayType = $ridershipRow['day_type'];
    $riderCount = $ridershipRow['rider_count'];
    $ridership[$monthfull][$dayType] = $riderCount;
  }
  return $ridership;
}

function getRidershipOneMonth($station, $monthfull, $entryOrExit = "entry") {
  global $mysqli;
  $ridershipQuery = "";
  if ($station == "total" && $entryOrExit == "entry") {
    $ridershipQuery = "select * from ridership_exit_total where monthfull=?;";
  } else if ($station == "total") {
    $ridershipQuery = "select * from ridership_entry_total where monthfull=?;";
  } else if ($entryOrExit == "entry") {
    $ridershipQuery = "select * from ridership where entry_station_code=? and monthfull=?;";
  } else if ($entryOrExit == "exit") {
    $ridershipQuery = "select * from ridership where exit_station_code=? and monthfull=?;";
  }
  $stmt = $mysqli -> prepare($ridershipQuery);
  if ($station == "total" && $entryOrExit == "entry") {
    $stmt -> bind_param("s", $monthfull);
  } else if ($station == "total") {
    $stmt -> bind_param("s", $monthfull);
  } else if ($entryOrExit == "entry") {
    $stmt -> bind_param("ss", $station, $monthfull);
  } else if ($entryOrExit == "exit") {
    $stmt -> bind_param("ss", $station, $monthfull);
  }
  $stmt -> execute();
  $ridershipResult = $stmt -> get_result();
  for ($i = 0; $i < $ridershipResult -> num_rows; $i++) {
    $ridershipRow = $ridershipResult -> fetch_assoc();
    $otherStation = "";
    if ($entryOrExit == "entry") {
      $otherStation = $ridershipRow['exit_station_code'];
    } else {
      $otherStation = $ridershipRow['entry_station_code'];
    }
    $dayType = $ridershipRow['day_type'];
    $riderCount = $ridershipRow['rider_count'];
    $ridership[$otherStation][$dayType] = $riderCount;
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
    $routeQuery = "select start_station_code, end_station_code, max(case when station_code = ? then time_from_start else case when start_station_code = ? then 0 else -1 end end) as time1, max(case when station_code = ? then time_from_start else case when start_station_code = ? then 0 else -1 end end) as time2 from routes where station_code in (?, ?) or start_station_code in (?, ?) group by start_station_code, end_station_code;";
    $stmt = $mysqli -> prepare($routeQuery);
    $stmt -> bind_param("ssssssss", $entryStation, $entryStation, $exitStation, $exitStation, $entryStation, $exitStation, $entryStation, $exitStation);
    $stmt -> execute();
    $routeResult = $stmt -> get_result();
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
  $nameQuery = "select ordinary_name from stations where code_2l = ?;";
  $stmt = $mysqli -> prepare($nameQuery);
  $stmt -> bind_param("s", $code_2l);
  $stmt -> execute();
  $nameResult = $stmt -> get_result();
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
  $stationsQuery = "select station_code, time_from_start from routes where start_station_code = ? and end_station_code = ? and $station_code != ? and time_from_start $symbol ?";
  $stmt = $mysqli -> prepare($stationsQuery);
  $stmt -> bind_param("ssss", $start_station_code, $end_station_code, $station_code, $time_from_start);
  $stmt -> execute();
  $stationsResult = $stmt -> get_result();
  $stationList = array();
  for($i = 0; $i < $stationsResult -> num_rows; $i++) {
    $stationsRow = $stationsResult -> fetch_assoc();
    array_push($stationList, $stationsRow);
  }
  return $stationList;
}

function getSortedRoutesList($station_code) {
  global $mysqli;
  $routesQuery = "select start_station_code, end_station_code, time_from_start from routes where station_code = ?;";
  $stmt = $mysqli -> prepare($routesQuery);
  $stmt -> execute();
  $routesResult = $stmt -> get_result();
  $stationArray = array();
  for ($i=0;$i < $routesResult -> num_rows; $i++) {
    $routesResultRow = $routesResult -> fetch_assoc();
    $start_station_code = $routesResultRow['start_station_code'];
    $end_station_code = $routesResultRow['end_station_code'];
    $time_from_start = $routesResultRow['time_from_start'];
  }
}

?>
