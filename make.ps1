param (
	[Parameter(Mandatory=$True)] [string[]]$target,
	[Parameter(Mandatory=$False)] [string]$prefix = "$pwd/build/windows",
	[Parameter(Mandatory=$False)] [string]$EXTRA_FLAGS,
	[Parameter(Mandatory=$False)] [string]$TRESS_ARG,
	[Parameter(Mandatory=$False)] [switch]$auto_setup
)

function make_absolute( [string]$path ) {
	if ( -Not( [System.IO.Path]::IsPathRooted( $path ) ) ) {
		$path = [IO.Path]::GetFullPath( [IO.Path]::Combine( ( ($pwd).Path ), ( $path ) ) )
	}
	return $path.Replace( "\", "/" )
}

function purge {
	Write-Host -NoNewline "Purging... "
	Remove-Item "build" -Recurse -ErrorAction Ignore
	Write-Host "done."
}

function build( [string]$config, [string]$extraFlags ) {
	New-Item -ItemType Directory -Force -Path "build/$config" > $null
	Push-Location "build/$config"
	cscript ../../configure.js PROJECT_ROOT=../../ BUILD_TYPE=$config $extraFlags
	cmake --build . --config $config
	Pop-Location
}

function test {
	build "debug"
	New-Item -ItemType Directory -Force -Path "out" > $null
	Remove-Item "out/tress.sqlite" -ErrorAction Ignore
	chcp 65001
	sqlite3 -init "data/sqlite.sql" "out/tress.sqlite" ".exit"
	$env:TZ="Europe/Warsaw"
	$env:TRESSRC="tressrc"
	$env:YAAL_AUTO_SANITY=1
	$env:YAAL_LOG_LEVEL="info"
	$env:DEFAULT_TARGET="debug"
	$env:TRESS_CLOCK_QUALITY_MULTIPLIER="256"
	if ( -Not( Test-Path env:BC_PATH ) ) {
		$env:BC_PATH="../windows/bin/bc.exe"
	}
	$null | .\build\debug\tress\1exec.exe -q $TRESS_ARG > $null
}

function debug( [string]$extraFlags = $EXTRA_FLAGS ) {
	build "debug" $extraFlags
}

function release( [string]$extraFlags = $EXTRA_FLAGS ) {
	build "release" $extraFlags
}

foreach ( $t in $target ) {
	if (
		( $t -ne "debug" ) -and
		( $t -ne "release" ) -and
		( $t -ne "test" ) -and
		( $t -ne "purge" )
	) {
		Write-Error "Unknown target: ``$t``"
		exit 1
	}
}

try {
	$origEnvPath=$env:Path
	$stackSize = ( Get-Location -Stack ).Count
	Push-Location $PSScriptRoot
	if ( Test-Path( "local.js" ) ) {
		Select-String -ErrorAction Ignore -Path "local.js" -Pattern "PREFIX\s*=\s*[`"]([^`"]+)[`"]" | ForEach-Object {
			$prefix = make_absolute( "$($_.Matches.groups[1])" )
		}
	} elseif ( $auto_setup ) {
		$prefix = make_absolute( $prefix )
		$local_js = (
			"PREFIX = `"$prefix`";`n" +
			"SYSCONFDIR = `"$prefix/etc`";`n" +
			"DATADIR = `"$prefix/share`";`n" +
			"LOCALSTATEDIR = `"$prefix/var`";`n" +
			"EXTRA_INCLUDE_PATH = `"$prefix/include`";`n" +
			"EXTRA_LIBRARY_PATH = `"$prefix/lib`";`n" +
			"VERBOSE = 1;`n" +
			"FAST = 1;`n"
		)
		$Utf8NoBomEncoding = New-Object System.Text.UTF8Encoding $False
		[System.IO.File]::WriteAllText( "$pwd/local.js", $local_js, $Utf8NoBomEncoding )
	}
	if ( $auto_setup ) {
		if ( $PSBoundParameters.ContainsKey( "EXTRA_FLAGS" ) ) {
			throw "You cannot specify EXTRA_FLAGS in auto_setup mode!"
		}
	}
	$env:Path = ( $env:Path.Split( ';')  | Where-Object { -Not( $_.ToLower().Contains( "cygwin" ) ) } ) -join ';'
	$env:Path = "$prefix\bin;$env:Path"
	foreach ( $t in $target ) {
		&$t
	}
} catch {
	Write-Error "$_"
	$LASTEXITCODE = 1
} finally {
	while ( ( Get-Location -Stack ).Count -gt $stackSize ) {
		Pop-Location
	}
	$env:Path=$origEnvPath
	exit $LASTEXITCODE
}

