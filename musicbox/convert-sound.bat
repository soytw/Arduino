@echo off
setlocal EnableDelayedExpansion
mkdir converted-sound
FOR /D %%d IN ("sound\*") DO (
	set prefix="%%~nd"
	echo !prefix!
	FOR %%s IN ("%%d\*.wav") DO (
		set base="%%~ns"
		set filename=!prefix! !base!
		echo !filename!
		echo "%%s -> converted-sound\!prefix:~0,3!_!base!.afm"
		rem tools\sox_win\sox "%%s" --norm=-1 -e unsigned-integer -b 8 -r 62500 -c 1 -t raw "converted-sound\!prefix:~0,3!_%%~ns.afm"
	)
)
pause
