<?php

function printRidership($entryStation, $exitStation) {
  global $monthList;
  $queryStartTime = microtime(true);
  $forwardRidership = getRidership($entryStation, $exitStation);
  $reverseRidership = getRidership($exitStation, $entryStation);
  $queryEndTime = microtime(true);
  $queryTimeTaken = $queryEndTime - $queryStartTime;
  print "<p>The table below shows average weekday, Saturday, and Sunday ridership between the stations $entryStation and $exitStation</p>";
  print "\n";
  $permalinkUrl = "https://bart.vipulnaik.com/ridership.php?entryStation=$entryStation&exitStation=$exitStation";
  print "<p>Permalink URL: <a href=\"$permalinkUrl\">$permalinkUrl</a></p>";
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
  $displayTimeTaken = $displayEndTime - $queryEndTime;
  print "<p>Printed data for ".count($monthList)." months (rows) and 6 columns, for a total of ".(count($monthList) * 6)." entries</p>";
  print "<p>Total time taken: ".sprintf('%.3f',$totalTimeTaken)." seconds, ".sprintf('%.3f',$queryTimeTaken)." for query and ".sprintf('%.3f',$displayTimeTaken)." for display</p>\n";
}
?>
