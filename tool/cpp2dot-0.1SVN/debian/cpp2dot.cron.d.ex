#
# Regular cron jobs for the cpp2dot package
#
0 4	* * *	root	[ -x /usr/bin/cpp2dot_maintenance ] && /usr/bin/cpp2dot_maintenance
