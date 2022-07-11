<?php

print '<td><select multiple name="'.$multipleMonthVariableName.'[]" size="10">';
for($i=0; $i < count($monthList); $i++) {
  print "<option value=\"".$monthList[$i]."\"";
  if ($monthVariableName == "month" and $monthList[$i] == $month) {
    print ' selected';
  }
  print ">".$monthList[$i]."</option>\n";
}
print "</select></td></tr>";
?>