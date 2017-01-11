#!/bin/bash
mkdir converted-sound 2> /dev/null
for dir in $(ls "sound"); do
	prefix="${dir:0:8}"
	for src in $(ls "sound/$dir"); do
		base="${src:0:-4}"
		echo "sound/$dir/$src -> converted-sound/$prefix/$base.wav"
		mkdir "converted-sound/$prefix" 2> /dev/null
		ffmpeg -i "sound/$dir/$src" -codec pcm_u8 -ar 16000 "converted-sound/$prefix/$base.wav" > /dev/null
	done
done
