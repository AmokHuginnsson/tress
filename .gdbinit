directory .:~/src/yaal:~/src/yaal/hcore:~/src/yaal/hconsole:~/src/yaal/hdata:~/src/yaal/tools
set solib-search-path ~/lib
set auto-solib-add on
set extension-language .h c++
set extension-language .c c++
set history filename .gdbhistory
set history save on
set print asm-demangle on
set print demangle on
set print pretty on
set print object on
define go
	run
	source .breaks
end
share
file ./build/1exec -readnow
break main
set language c++
source .gdb_local
#core-file ./1exec.core
#run
