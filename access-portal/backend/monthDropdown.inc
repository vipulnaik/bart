<?php

print '<td><select name="'.$monthVariableName.'">';
for($i=0; $i < count($monthList); $i++) {
  print "<option value=\"".$monthList[$i]."\" ";
  if ($monthVariableName == "month" and isset($month) and $monthList[$i] == $month) {
    print ' selected';
  }
  print ">".$monthList[$i]."</option>\n";
}
print "</select></td></tr>";
?>