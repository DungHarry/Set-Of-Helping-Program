<?php
	/*
        	Author: Dung Harry
        	Date created: 21st, February 2016
        	Operating System: Ubuntu Desktop 15.10 i386
        	Server: Apache2 / PHP version 5.6.11

        	Description: this is the example about how to display current time in P$
	*/

	$time = time();

	echo "The current time is: " . date("Y-m-d H:i:s", $time);
?>
