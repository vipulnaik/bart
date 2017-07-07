<?php
$mysqli = new mysqli("localhost", "database name", "password", "username");
$mysqli->set_charset("utf8");
$imagesPath = "(project folder)/access-portal/images/";
$generateGraphCmdBase = "python3.5 /home/antivipulnaik/git/bart/python/graph.py --label ";
?>