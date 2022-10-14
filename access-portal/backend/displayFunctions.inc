<?php

function printStationData($unsafeStationList) {
  global $mysqli;
  if (count($unsafeStationList) == 0) {
    return;
  }
  $stationList = array();
  foreach ($unsafeStationList as $station) {
    if (strlen($station) == 2 and ctype_alnum($station)) {
      array_push($stationList, $station);
    }
  }
  $stationListString = "(\"".join( "\",\"", $stationList)."\")";
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
  if ($entryStation == "total" or $exitStation == "total") {
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
  global $mysqli;
  $queryStartTime = microtime(true);
  $allStations = array();
  $query = "select * from stations where opening_date <= ".'"'.str_replace('"','\"',$monthfull)."-28".'"'." order by ordinary_name;";
  $result = $mysqli -> query($query);
  for($i = 0; $i < $result -> num_rows; $i++) {
    $row = $result -> fetch_assoc();
    array_push($allStations, $row['code_2l']);
    $fullStationName[$row['code_2l']] = $row['ordinary_name'];
    $openingDate[$row['code_2l']] = $row['opening_date'];
  }
  if ($station != "total" and !isset($fullStationName[$station])) {
    print "<p>The station ".getStationName($station)." ($station) was not yet open for revenue service as of the month $monthfull that you have selected. Therefore we have no fare, time, or ridership data to print. Please select a month containing or after the opening date of the station printed in the table above.</p>";
    return;
  }
  $entryRidership = getRidershipOneMonth($station, $monthfull, "entry");
  $exitRidership = getRidershipOneMonth($station, $monthfull, "exit");
  foreach ($allStations as $otherStation) {
    $routesAndTimes = getRoutesAndTimes($station, $otherStation);
    if (count($routesAndTimes) > 0) {
      $timeForStation[$otherStation] = $routesAndTimes[0]['time'];
    } else {
      $routesAndTimesPairs = getRoutesAndTimesIndirect($station, $otherStation);
      if (count($routesAndTimesPairs) > 0) {
        $totalTime = $routesAndTimesPairs[0]['leg1'][0]['time'] + $routesAndTimesPairs[0]['leg2'][0]['time'];
        $timeForStation[$otherStation] = $totalTime;
      } else {
        $timeForStation[$otherStation] = "";
      }
    }
    $fareForStation[$otherStation] = getApplicableFareForMonth($station, $otherStation, $monthfull);
  }
  $queryEndTime = microtime(true);
  $queryTimeTaken = $queryEndTime - $queryStartTime;
  if ($station != "total") {
    print "<p>Note that fare data may not be accurate for months older than February 2016, as we have not entered the full history of fare schedules yet. Also, time data is estimated and may be missing or inaccurate for some station pairs.</p>\n";
  }
  print '<table id="ridershipData" class="tablesorter">'."\n";
  print "<thead>\n";
  print "    <tr>\n";
  print "      <th>Other station</th>\n";
  if ($station != "total") {
    print "      <th>Travel time</th>\n";
    print "      <th>Fare</th>\n";
  }
  print "      <th>Weekday $station -> row station</th>\n";
  print "      <th>Weekday row station -> $station</th>\n";
  print "      <th>Saturday $station -> row station</th>\n";
  print "      <th>Saturday row station -> $station</th>\n";
  print "      <th>Sunday $station -> row station</th>\n";
  print "      <th>Sunday row station -> $station</th>\n";
  print "    </tr>\n";
  print "</thead>\n";
  print "<tbody>\n";
  foreach ($allStations as $otherStation) {
    print "    <tr>\n";
    print "      <td><a href=\"/ridership.php?entryStation=$station&exitStation=$otherStation\">".$fullStationName[$otherStation]." ($otherStation)</a></td>";
    if ($station != "total") {
      print "      <td align=\"right\">$timeForStation[$otherStation]</td>\n";
      print "      <td align=\"right\">$fareForStation[$otherStation]</td>\n";
    }
    print "      <td align=\"right\">".$entryRidership[$otherStation]['weekday']."</td>\n";
    print "      <td align=\"right\">".$exitRidership[$otherStation]['weekday']."</td>\n";
    print "      <td align=\"right\">".$entryRidership[$otherStation]['saturday']."</td>\n";
    print "      <td align=\"right\">".$exitRidership[$otherStation]['saturday']."</td>\n";
    print "      <td align=\"right\">".$entryRidership[$otherStation]['sunday']."</td>\n";
    print "      <td align=\"right\">".$exitRidership[$otherStation]['sunday']."</td>\n";
    print "    </tr>\n";
  }
  print "</tbody>\n";
  print "</table>";
  $displayEndTime = microtime(true);
  $displayTimeTaken = $displayEndTime - $queryEndTime;
  $totalTimeTaken = $displayEndTime - $queryStartTime;
  print "<p>Printed data for ".count($allStations)." stations (rows) and 8 columns (excluding header column), for a total of ".(count($allStations) * 8)." entries</p>";
  print "<p>Total time taken: ".sprintf('%.3f',$totalTimeTaken)." seconds, ".sprintf('%.3f',$queryTimeTaken)." for query and ".sprintf('%.3f',$displayTimeTaken)." for display</p>\n";  
}

function printListRidership($entryStationsList, $exitStationsList) {
  global $monthList;
  global $imagesPath;
  global $generateGraphCmdBase;
  $queryStartTime = microtime(true);
  $permalinkUrl = "https://bart.vipulnaik.com/ridership-multiple.php?";
  for ($i = 0; $i < count($entryStationsList); $i++) {
    $permalinkUrl .= "entryStationsList[".$i."]=".$entryStationsList[$i]."&";
  }
  for ($i = 0; $i < count($exitStationsList); $i++) {
    $permalinkUrl .= "exitStationsList[".$i."]=".$exitStationsList[$i];
    if ($i < count($exitStationsList) - 1) {
      $permalinkUrl .= "&";
    }
  }
  print "<p>Permalink URL: <a href=\"$permalinkUrl\">$permalinkUrl</a></p>";
  $forwardRidership = getRidership($entryStationsList, $exitStationsList);
  $entryStationsListString = join(",",$entryStationsList);
  $exitStationsListString = join(",",$exitStationsList);
  if ($entryStationsList != $exitStationsList) {
    $reverseRidership = getRidership($exitStationsList, $entryStationsList);
  }
  $queryEndTime = microtime(true);
  $queryTimeTaken = $queryEndTime - $queryStartTime;
  $fullOutput = "Month|Weekday $entryStationsListString -> $exitStationsListString|Weekday $exitStationsListString -> $entryStationsListString|Saturday $entryStationsListString -> $exitStationsListString|Saturday $exitStationsListString -> $entryStationsListString|Sunday $entryStationsListString -> $exitStationsListString|Sunday $exitStationsListString -> $entryStationsListString";
  if ($entryStationsList == $exitStationsList) {
    $fullOutput = "Month|Weekday $entryStationsListString -> $exitStationsListString|Saturday $entryStationsListString -> $exitStationsListString|Sunday $entryStationsListString -> $exitStationsListString";
  }
  $fullOutput .= "\n";
  foreach ($monthList as $monthfull) {
    $fullOutput .= $monthfull;
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['weekday'];
    if ($entryStationsList != $exitStationsList) {
      $fullOutput .= '|';
      $fullOutput .= $reverseRidership[$monthfull]['weekday'];
    }
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['saturday'];
    if ($entryStationsList != $exitStationsList) {
      $fullOutput .= '|';
      $fullOutput .= $reverseRidership[$monthfull]['saturday'];
    }
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['sunday'];
    if ($entryStationsList != $exitStationsList) {
      $fullOutput .= '|';
      $fullOutput .= $reverseRidership[$monthfull]['sunday'];     
    }
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
    # print "<br/> Excuting $cmdToExecute";
    exec($cmdToExecute);
  }

  print '<img src="/images/'.$fileName.'-timeseries.png" alt="Graph of ridership should have loaded here"></img>';
  $graphEndTime = microtime(true);
  $graphTimeTaken = $graphEndTime - $queryEndTime;
  print "\n";
  print '<table id="ridershipData" class="tablesorter">'."\n";
  print "  <thead>";
  print "    <tr>\n";
  print "      <th>Year</th>\n";
  print "      <th>Month</th>\n";
  print "      <th>Weekday $entryStationsListString -> $exitStationsListString</th>\n";
  if ($entryStationsList != $exitStationsList) {
    print "      <th>Weekday $exitStationsListString -> $entryStationsListString</th>\n";
  }
  print "      <th>Saturday $entryStationsListString -> $exitStationsListString</th>\n";
  if ($entryStationsList != $exitStationsList) {
    print "      <th>Saturday $exitStationsListString -> $entryStationsListString</th>\n";
  }
  print "      <th>Sunday $entryStationsListString -> $exitStationsListString</th>\n";
  if ($entryStationsList != $exitStationsList) {
    print "      <th>Sunday $exitStationsListString -> $entryStationsListString</th>\n";
  }
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
    if ($entryStationsList != $exitStationsList) {
      print "      <td align=\"right\">".$reverseRidership[$monthfull]['weekday']."</td>\n";
    }
    print "      <td align=\"right\">".$forwardRidership[$monthfull]['saturday']."</td>\n";
    if ($entryStationsList != $exitStationsList) {
      print "      <td align=\"right\">".$reverseRidership[$monthfull]['saturday']."</td>\n";
    }
    print "      <td align=\"right\">".$forwardRidership[$monthfull]['sunday']."</td>\n";
    if ($entryStationsList != $exitStationsList) {
      print "      <td align=\"right\">".$reverseRidership[$monthfull]['sunday']."</td>\n";
    }
    print "    </tr>";
  }
  print "  </tbody>\n";
  print "</table>\n";
  $displayEndTime = microtime(true);
  $totalTimeTaken = $displayEndTime - $queryStartTime;
  $displayTimeTaken = $displayEndTime - $graphEndTime;
  $numColumns = 3;
  if ($entryStationsList != $exitStationsList) {
    $numColumns = 6;
  }
  print "<p>Printed data for ".count($monthList)." months (rows) and $numColumns columns, for a total of ".(count($monthList) * $numColumns)." entries</p>";
  print "<p>Total time taken: ".sprintf('%.3f',$totalTimeTaken)." seconds, ".sprintf('%.3f',$queryTimeTaken)." for query, ".sprintf('%.3f',$graphTimeTaken)." for graph, and ".sprintf('%.3f',$displayTimeTaken)." for display</p>\n";
}

function printRidership($entryStation, $exitStation) {
  global $monthList;
  global $imagesPath;
  global $generateGraphCmdBase;
  $queryStartTime = microtime(true);
  $permalinkUrl = "https://bart.vipulnaik.com/ridership.php?entryStation=$entryStation&exitStation=$exitStation";
  $forwardRidership = getRidership(array($entryStation), array($exitStation));
  if ($entryStation != $exitStation) {
    $reverseRidership = getRidership(array($exitStation), array($entryStation));
  }
  $queryEndTime = microtime(true);
  $queryTimeTaken = $queryEndTime - $queryStartTime;
  $entryStationInfo = expandStationInfo($entryStation);
  $exitStationInfo = expandStationInfo($exitStation);
  print "<p>The graph and table below show average weekday, Saturday, and Sunday ridership between $entryStationInfo and $exitStationInfo.</p>";
  $fullOutput = "Month|Weekday $entryStation -> $exitStation|Weekday $exitStation -> $entryStation|Saturday $entryStation -> $exitStation|Saturday $exitStation -> $entryStation|Sunday $entryStation -> $exitStation|Sunday $exitStation -> $entryStation\n";
  if ($entryStation == $exitStation) {
    $fullOutput = "Month|Weekday $entryStation -> $exitStation|Saturday $entryStation -> $exitStation|Sunday $entryStation -> $exitStation\n";
  }
  foreach ($monthList as $monthfull) {
    $fullOutput .= $monthfull;
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['weekday'];
    if ($entryStation != $exitStation) {
      $fullOutput .= '|';
      $fullOutput .= $reverseRidership[$monthfull]['weekday'];
    }
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['saturday'];
    if ($entryStation != $exitStation) {
      $fullOutput .= '|';
      $fullOutput .= $reverseRidership[$monthfull]['saturday'];
    }
    $fullOutput .= '|';
    $fullOutput .= $forwardRidership[$monthfull]['sunday'];
    if ($entryStation != $exitStation) {
      $fullOutput .= '|';
      $fullOutput .= $reverseRidership[$monthfull]['sunday'];
    }
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

  print '<img src="/images/'.$fileName.'-timeseries.png" alt="Graph of ridership should have loaded here"></img>';
  $graphEndTime = microtime(true);
  $graphTimeTaken = $graphEndTime - $queryEndTime;
  print "\n";
  print '<table id="ridershipData" class="tablesorter">'."\n";
  print "  <thead>";
  print "    <tr>\n";
  print "      <th>Year</th>\n";
  print "      <th>Month</th>\n";
  print "      <th>Weekday $entryStation -> $exitStation</th>\n";
  if ($entryStation != $exitStation) {
    print "      <th>Weekday $exitStation -> $entryStation</th>\n";
  }
  print "      <th>Saturday $entryStation -> $exitStation</th>\n";
  if ($entryStation != $exitStation) {
    print "      <th>Saturday $exitStation -> $entryStation</th>\n";
  }
  print "      <th>Sunday $entryStation -> $exitStation</th>\n";
  if ($entryStation != $exitStation) {
    print "      <th>Sunday $exitStation -> $entryStation</th>\n";
  }
  print "    </tr>\n";
  print "  </thead>\n";
  print "  <tbody>\n";
  foreach ($monthList as $monthfull) {
    print "    <tr>";
    $yearOnly = substr($monthfull,0,4);
    $monthOnly = substr($monthfull,5,7);
    print "      <td align=\"right\">$yearOnly</td>\n";
    print "      <td align=\"right\">$monthOnly</td>\n";
    if (isset($forwardRidership[$monthfull] and isset($reverseRidership[$monthfull]))) {
      print "      <td align=\"right\">".$forwardRidership[$monthfull]['weekday']."</td>\n";
      if ($entryStation != $exitStation) {
        print "      <td align=\"right\">".$reverseRidership[$monthfull]['weekday']."</td>\n";
      }
      print "      <td align=\"right\">".$forwardRidership[$monthfull]['saturday']."</td>\n";
      if ($entryStation != $exitStation) {
        print "      <td align=\"right\">".$reverseRidership[$monthfull]['saturday']."</td>\n";
      }
      print "      <td align=\"right\">".$forwardRidership[$monthfull]['sunday']."</td>\n";
      if ($entryStation != $exitStation) {
        print "      <td align=\"right\">".$reverseRidership[$monthfull]['sunday']."</td>\n";
      }
    }
    print "    </tr>";
  }
  print "  </tbody>\n";
  print "</table>\n";
  $displayEndTime = microtime(true);
  $totalTimeTaken = $displayEndTime - $queryStartTime;
  $displayTimeTaken = $displayEndTime - $graphEndTime;
  $numColumns = 3;
  if ($entryStation != $exitStation) {
    $numColumns = 6;
  }
  print "<p>Printed data for ".count($monthList)." months (rows) and $numColumns columns, for a total of ".(count($monthList) * $numColumns)." entries</p>";
  print "<p>Total time taken: ".sprintf('%.3f',$totalTimeTaken)." seconds, ".sprintf('%.3f',$queryTimeTaken)." for query, ".sprintf('%.3f',$graphTimeTaken)." for graph, and ".sprintf('%.3f',$displayTimeTaken)." for display</p>\n";
}
?>
