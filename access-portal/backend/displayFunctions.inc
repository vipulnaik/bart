<?php

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
  print "<p>The graph and table below shows average weekday, Saturday, and Sunday ridership between the stations $entryStation and $exitStation</p>";
  print "<p>Permalink URL: <a href=\"$permalinkUrl\">$permalinkUrl</a></p>";
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
  print "<p>Printed data for ".count($monthList)." months (rows) and 6 columns, for a total of ".(count($monthList) * 6)." entriese</p>";
  print "<p>Total time taken: ".sprintf('%.3f',$totalTimeTaken)." seconds, ".sprintf('%.3f',$queryTimeTaken)." for query, ".sprintf('%.3f',$graphTimeTaken)." for graph, and ".sprintf('%.3f',$displayTimeTaken)." for display</p>\n";
}
?>
