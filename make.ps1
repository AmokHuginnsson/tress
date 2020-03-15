param (
	[Parameter(Mandatory=$True)] [string]$target,
	[Parameter(Mandatory=$False)] [string]$prefix = "$pwd/build/windows",
	[Parameter(Mandatory=$False)] [string]$EXTRA_FLAGS,
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

function debug( [string]$extraFlags = $EXTRA_FLAGS ) {
	build "debug" $extraFlags
}

function release( [string]$extraFlags = $EXTRA_FLAGS ) {
	build "release" $extraFlags
}

if (
	( $target -ne "debug" ) -and
	( $target -ne "release" ) -and
	( $target -ne "purge" )
) {
	Write-Error "Unknown target: ``$target``"
	exit 1
}

try {
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
			throw "You cannot specify $EXTRA_FLAGS in $auto_setup mode!"
		}
	}
	$origEnvPath=$env:Path
	$env:Path = ( $env:Path.Split( ';')  | Where-Object { -Not( $_.ToLower().Contains( "cygwin" ) ) } ) -join ';'
	$env:Path = "$prefix\bin;$env:Path"
	&$target
} catch {
	Pop-Location
	Write-Error "$_"
} finally {
	$env:Path=$origEnvPath
}

