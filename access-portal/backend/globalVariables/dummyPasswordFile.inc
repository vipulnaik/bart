<?php
$mysqli = new mysqli("localhost", "database name", "password", "username");
$mysqli->set_charset("utf8mb4");
$imagesPath = "(project folder)/access-portal/images/";
$generateGraphCmdBase = "python3 /home/antivipulnaik/git/bart/python/graph.py --label ";
?>
