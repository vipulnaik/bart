<?php

function printStationData($stationList) {
  global $mysqli;
  if (count($stationList) == 0) {
    return;
  }
  $stationListString = "('".join("','",$stationList)."')";
  $stationDataQuery = "select * from stations where code_2l in $stationListString";
  $stationDataResult = $mysqli -> query($stationDataQuery);
  for($i = 0; $i < $stationDataResult -> num_rows; $i++) {
    $stationDataRow = $stationDataResult -> fetch_assoc();
    $stationData[$stationDataRow['code_2l']] = $stationDataRow;
  }
  print '<table border="1">'."\n";
  print "    <tr>\n";
  print "      <th>Field name</th>\n";
  foreach ($stationList as $station) {
    print "      <th>Value for station $station</th>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>2-letter code (used in ridership reports; see <a href=\"https://www.bart.gov/sites/default/files/docs/Station_Names.xls\">Station Name Abbreviations (XLS)</a>)</td>\n";
  foreach ($stationList as $station) {
    print "      <td>$station</td>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>4-letter code (used in APIs and on BART website)</td>\n";
  foreach ($stationList as $station) {
    print "      <td>".$stationData[$station]['code_4l']."</td>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>Long code (used in fares and schedules brochure)</td>\n";
  foreach ($stationList as $station) {
    print "      <td>".$stationData[$station]['code_long']."</td>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>Ordinary name</td>\n";
  foreach ($stationList as $station) {
    print "     <td>".$stationData[$station]['ordinary_name']."</td>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>Wikipedia page</td>\n";
  foreach ($stationList as $station) {
    print "     <td><a href=\"".$stationData[$station]['wikipedia_page']."\">".$stationData[$station]['wikipedia_page']."</a></td>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>BART page</td>\n";
  foreach ($stationList as $station) {
    print "     <td><a href=\"".$stationData[$station]['bart_page']."\">".$stationData[$station]['bart_page']."</a></td>\n";
  }
  print "    </tr>\n";
  print "    <tr>\n";
  print "      <td>Opening date</td>\n";
  foreach ($stationList as $station) {
    print "     <td>".$stationData[$station]['opening_date']."</td>\n";
  }
  print "    </tr>\n";
  print "</table>\n";
}

function printRoutesAndFares($entryStation, $exitStation) {
  $routesAndTimes = getRoutesAndTimes($entryStation, $exitStation);
  $faresAndEffectiveDates = getFaresAndEffectiveDates($entryStation, $exitStation);
  if ($entryStation == "total" and $exitStation == "total") {
  } else if ($entryStation == $exitStation) {
    print "<p>Since the entry and exit station are the same, the effective fare is $0 if you do not enter BART. However, if you do enter BART at the station and exit it again at the same station, you are charged the excursion fare of $5.75.</p>\n";
  } else {
    print "\n";
    print "<p>Fare between stations ".getStationName($entryStation)." and ".getStationName($exitStation).":</p>\n";
    print "<ul>\n";
    for ($i=0; $i < count($faresAndEffectiveDates); $i++) {
      print "    <li><p>Fare of $".sprintf('%.2f',$faresAndEffectiveDates[$i]['fare'])." effective since ".$faresAndEffectiveDates[$i]['effective_date']."</p></li>\n";
    }
  }
  print "</ul>\n";
  if ($entryStation == "total" or $exitStation == "total") {
  } else if ($entryStation == $exitStation) {
    print "<p>Entry and exit station are the same</p>";
  } else if (count($routesAndTimes) > 0) {
    print "<p>List of direct routes available below:</p>"; 
    print "<ul>";
    foreach($routesAndTimes as $routeAndTime) {
      print "<li><p>".$routeAndTime['time']." minute";
      if ($routeAndTime['time'] != 1) {
        print "s";
      }
      print " on route ".getStationName($routeAndTime['start'])." -> ".getStationName($routeAndTime['end'])."</p></li>";
    }
    print "</ul>";   
  } else {
    $routesAndTimesPairs = getRoutesAndTimesIndirect($entryStation, $exitStation);
    if (count($routesAndTimesPairs) > 0) {
      print "<p>No direct routes available between ".getStationName($entryStation)." and ".getStationName($exitStation).". List of indirect routes available below.</p>\n";
      print "<ul>\n";
      foreach($routesAndTimesPairs as $routesAndTimesPair) {
        $timeForThisJourney =  $routesAndTimesPair['leg1'][0]['time'] + $routesAndTimesPair['leg2'][0]['time'];
        print "    <li><p>Transfer via the station ".getStationName($routesAndTimesPair['transferStation']).", total time $timeForThisJourney minutes (excluding time taken waiting for transfer).</p>\n";
        print "      <ul>\n";
        print "        <li><p>Leg 1</p>\n";
        print "          <ul>\n";
        foreach ($routesAndTimesPair['leg1'] as $routeAndTime) {
          print "<li><p>".$routeAndTime['time']." minutes on route ".getStationName($routeAndTime['start'])." -> ".getStationName($routeAndTime['end'])."</p></li>";
        }
        print "          </ul></li>\n";
        print "        <li><p>Leg 2</p>\n";
        print "          <ul>\n";
        foreach ($routesAndTimesPair['leg2'] as $routeAndTime) {
          print "<li><p>".$routeAndTime['time']." minutes on route ".getStationName($routeAndTime['start'])." -> ".getStationName($routeAndTime['end'])."</p></li>";
        }
        print "          </ul></li>\n";
        print "      </ul>\n";
        print "    </li>\n";
      }
      print "</ul>\n";
    } else {
      print "<p>No direct or indirect routes available between $entryStation and $exitStation.</p>";
    }
  }
}

function expandStationInfo($station) {
  if ($station == "total") {
    return "all stations";
  } else {
    $stationName = getStationName($station);
    return "the station $stationName ($station)";
  }
}

function printRidershipOneMonth($station, $monthfull) {
  $entryRidership = getRidershipOneMonth($station, $monthfull, "entry");
  $exitRidership = getRidershipOneMonth($station, $monthfull, "exit");
  $allStations = array_keys($entryRidership);
  sort($allStations);
  print '<table id="ridershipData" class="tablesorter">'."\n";
  print "<thead>\n";
  print "    <tr>\n";
  print "      <th>Travel time</th>\n";
  print "      <th>Fare</th>\n";
  print "      <th>Other station</th>\n";
  print "      <th>Weekday $station -> $otherStation</th>\n";
  print "      <th>Weekday $otherStation -> $station</th>\n";
  print "      <th>Saturday $station -> $otherStation<th>\n";
  print "      <th>Saturday $otherStation -> $station</th>\n";
  print "      <th>Sunday $station -> $otherStation</th>\n";
  print "      <th>Sunday $otherStation -> $station</th>\n";
  print "    </tr>\n";
  print "</thead>\n";
  print "<tbody>\n";
  foreach ($allStations as $otherStation) {
    print "    <tr>\n";
    print "      <td>".getStationName($otherStation)." ($otherStation)</td>";
    $routesAndTimes = getRoutesAndTimes($station, $otherStation);
    if (count($routesAndTimes) > 0) {
      print "      <td>".$routesAndTimes[0]['time']."</td>\n";
    } else {
      print "      <td></td>\n";
    }
    print "      <td></td>\n";
    print "      <td>".$entryRidership[$otherStation]['weekday']."</td>\n";
    print "      <td>".$exitRidership[$otherStation]['weekday']."</td>\n";
    print "      <td>".$entryRidership[$otherStation]['saturday']."</td>\n";
    print "      <td>".$exitRidership[$otherStation]['saturday']."</td>\n";
    print "      <td>".$entryRidership[$otherStation]['sunday']."</td>\n";
    print "      <td>".$exitRidership[$otherStation]['sunday']."</td>\n";
    print "    <tr>\n";
  }
  print "</table>";
}

function printRidership($entryStation, $exitStation) {
  global $monthList;
  global $imagesPath;
  global $generateGraphCmdBase;
  $queryStartTime = microtime(true);
  $permalinkUrl = "https://bart.vipulnaik.com/ridership.php?entryStation=$entryStation&exitStation=$exitStation";
  $forwardRidership = getRidership($entryStation, $exitStation);
  $reverseRidership = getRidership($exitStation, $entryStation);
  $queryEndTime = microtime(true);
  $queryTimeTaken = $queryEndTime - $queryStartTime;
  $entryStationInfo = expandStationInfo($entryStation);
  $exitStationInfo = expandStationInfo($exitStation);
  print "<p>The graph and table below shows average weekday, Saturday, and Sunday ridership between $entryStationInfo and $exitStationInfo.</p>";
  $fullOutput = "Month|WeekdayF|WeekdayB|SaturdayF|SaturdayB|SundayF|SundayB\n";
  foreach ($monthList as $monthfull) {
    $fullOutput .= $monthfull;
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['weekday'];
    $fullOutput .= '|';
    $fullOutput .= $reverseRidership[$monthfull]['weekday'];
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['saturday'];
    $fullOutput .= '|';
    $fullOutput .= $reverseRidership[$monthfull]['saturday'];
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['sunday'];
    $fullOutput .= '|';
    $fullOutput .= $reverseRidership[$monthfull]['sunday'];
    $fullOutput .= "\n";
  }
  $fileName = hash("md5",$permalinkUrl);
  $filePathBase = $imagesPath . $fileName;
  $dataHasChanged = false;
  if (file_exists($filePathBase . ".csv") == false) {
    # print "<br/>There is no file with the CSV $filePathBase . csv, so we are writing it out<br/>";
    file_put_contents($filePathBase . ".csv", $fullOutput);
    $dataHasChanged = true;
  } else {
    $previousOutput = file_get_contents($filePathBase . ".csv");
    if ($previousOutput != $fullOutput) {
      # print "<br/>We have a cached file but the underlying data has changed<br/><br/>";
      $dataHasChanged = true;
      file_put_contents($filePathBase . ".csv", $fullOutput);
    } else {
      # print "<br/>The cached file contents match the existing data<br/><br/>";
    }
  }
  $cmdToExecute = $generateGraphCmdBase . " " . $filePathBase . ".csv " . $filePathBase . "-timeseries.png";
  if ($dataHasChanged == true or file_exists($filePathBase . "-timeseries.png") == false) {
    if (file_exists($filePathBase . "-timeseries.png") == true) {
      exec("rm ".$filePathBase . "-timeseries.png");
    }
    exec($cmdToExecute);
  }

  print '<img src="/images/'.$fileName.'-timeseries.png" alt="Graph of pageviews should have loaded here"></img>';
  $graphEndTime = microtime(true);
  $graphTimeTaken = $graphEndTime - $queryEndTime;
  print "\n";
  print '<table id="ridershipData" class="tablesorter">'."\n";
  print "  <thead>";
  print "    <tr>\n";
  print "      <th>Year</th>\n";
  print "      <th>Month</th>\n";
  print "      <th>Weekday $entryStation -> $exitStation</th>\n";
  print "      <th>Weekday $exitStation -> $entryStation</th>\n";
  print "      <th>Saturday $entryStation -> $exitStation</th>\n";
  print "      <th>Saturday $exitStation -> $entryStation</th>\n";
  print "      <th>Sunday $entryStation -> $exitStation</th>\n";
  print "      <th>Sunday $exitStation -> $entryStation</th>\n";
  print "    </tr>\n";
  print "  </thead>\n";
  print "  <tbody>\n";
  foreach ($monthList as $monthfull) {
    print "    <tr>";
    $yearOnly = substr($monthfull,0,4);
    $monthOnly = substr($monthfull,5,7);
    print "      <td align=\"right\">$yearOnly</td>\n";
    print "      <td align=\"right\">$monthOnly</td>\n";
    print "      <td align=\"right\">".$forwardRidership[$monthfull]['weekday']."</td>\n";
    print "      <td align=\"right\">".$reverseRidership[$monthfull]['weekday']."</td>\n";
    print "      <td align=\"right\">".$forwardRidership[$monthfull]['saturday']."</td>\n";
    print "      <td align=\"right\">".$reverseRidership[$monthfull]['saturday']."</td>\n";
    print "      <td align=\"right\">".$forwardRidership[$monthfull]['sunday']."</td>\n";
    print "      <td align=\"right\">".$reverseRidership[$monthfull]['sunday']."</td>\n";
    print "    </tr>";
  }
  print "  </tbody>\n";
  print "</table>\n";
  $displayEndTime = microtime(true);
  $totalTimeTaken = $displayEndTime - $queryStartTime;
  $displayTimeTaken = $displayEndTime - $graphEndTime;
  print "<p>Printed data for ".count($monthList)." months (rows) and 6 columns, for a total of ".(count($monthList) * 6)." entries</p>";
  print "<p>Total time taken: ".sprintf('%.3f',$totalTimeTaken)." seconds, ".sprintf('%.3f',$queryTimeTaken)." for query, ".sprintf('%.3f',$graphTimeTaken)." for graph, and ".sprintf('%.3f',$displayTimeTaken)." for display</p>\n";
}
?>
