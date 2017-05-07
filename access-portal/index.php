<?php
print '<!doctype html public "-//W3C//DTD HTML 4.01 Transitional//EN"><html><head><meta http-equiv="Content-Type" content="text/html;charset=utf-8" >';
print '<title>BART: Historical ridership, route, and price data</title>';
# include_once('analytics.inc');
# include_once('backend/stringFunctions.inc');
print '<link href="style.css" rel="stylesheet" type="text/css" />'."\n";
print '<script type="text/javascript" src="./jquery-3.1.1.min.js"></script>'."\n";
print '<script type="text/javascript" src="./jquery.tablesorter.js"></script>'."\n";
print '</head>';
print '<body>';
print '<script>$(document).ready(function()
    {
        $("#myTableDonationAmountsByCauseAreaAndYear").tablesorter();
        $("#myTableDonationAmountsByDonorAndYear").tablesorter();	
        $("#myTableDonationAmountsByDoneeAndYear").tablesorter();	
    }
); </script>'."\n";

print '</body>';
?>
