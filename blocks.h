//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"LOAD ", "cut -d' ' -f1 /proc/loadavg",	5,	0},
	{"MEM ", "free -h | awk '/^Mem:/ {print $3\"/\"$2}' | sed 's/i//g'",	15,	0},
	{"TMP ", "for z in /sys/class/thermal/thermal_zone*/temp; do [ -r \"$z\" ] || continue; awk '{printf \"%.1fC\", $1/1000}' \"$z\"; break; done",	10,	0},
	{"NET ", "iface=$(ip route 2>/dev/null | awk '/^default/ {print $5; exit}'); [ -n \"$iface\" ] && state=$(cat /sys/class/net/\"$iface\"/operstate 2>/dev/null) && printf '%s:%s' \"$iface\" \"$state\"",	5,	0},
	{"VOL ", "wpctl get-volume @DEFAULT_AUDIO_SINK@ 2>/dev/null | awk '{v=int($2*100); if ($3==\"[MUTED]\") printf \"%d%% M\", v; else printf \"%d%%\", v}'",	2,	10},
	{"BAT ", "for b in /sys/class/power_supply/BAT*; do [ -r \"$b/capacity\" ] || continue; cap=$(cat \"$b/capacity\" 2>/dev/null); st=$(cat \"$b/status\" 2>/dev/null); printf '%s%% %s' \"$cap\" \"$st\"; break; done",	20,	0},
	{"", "date '+%b %d (%a) %I:%M%p'",					5,		0},
	
	/* Updates whenever "pkill -SIGRTMIN+10 someblocks" is ran */
	/* {"", "date '+%b %d (%a) %I:%M%p'",					0,		10}, */
};



//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "  |  ";
static unsigned int delimLen = 5;
