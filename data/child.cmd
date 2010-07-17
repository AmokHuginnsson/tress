@echo off
rem ! /bin/sh

set LOG_FILE=".\out\hpipedchild.log"

if exist %LOG_FILE%	del %LOG_FILE%

call:log "child start ..."

set /p LINE=

call:log "read input: %LINE%"

if "%LINE%" == "out" ( echo hello-OUT ) else if "%LINE%" == "err" ( echo hello-ERR 1>&2 ) else (
	echo error
	echo error 1>&2
)

call:log "written output ..."
call:log "exiting"

exit 0

:log
	date /T >> %LOG_FILE%
	time /T >> %LOG_FILE%
 	echo %~1 >> %LOG_FILE%
goto:eof

