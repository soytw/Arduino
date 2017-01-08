#!/bin/bash
mkdir converted-sound 2> /dev/null
for dir in $(ls "sound"); do
	prefix="${dir:0:3}"
	for src in $(ls "sound/$dir"); do
		base="${src:0:-4}"
		echo "sound/$dir/$src -> converted-sound/$prefix-$base.afm"
		tools/sox_win/sox "sound/$dir/$src" --norm=-1 -e unsigned-integer -b 8 -r 62500 -c 1 -t raw "converted-sound/$prefix-$base.afm"
	done
done
