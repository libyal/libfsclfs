# Script that synchronizes the local library dependencies
#
# Version: 20170722

$GitUrlPrefix = "https://github.com/libyal"
$LocalLibs = "libbfio libcdata libcerror libcfile libclocale libcnotify libcpath libcsplit libcthreads libfcache libfdata libfdatetime libfguid libftxf libftxr libfusn libfwnt libuna"
$LocalLibs = ${LocalLibs} -split " "

$Git = "git"
$WinFlex = "..\win_flex_bison\win_flex.exe"
$WinBison = "..\win_flex_bison\win_bison.exe"

ForEach (${LocalLib} in ${LocalLibs})
{
	# Split will return an array of a single empty string when LocalLibs is empty.
	If (-Not (${LocalLib}))
	{
		Continue
	}
	# PowerShell will raise NativeCommandError if git writes to stdout or stderr
	# therefore 2>&1 is added and the output is stored in a variable.
	$Output = Invoke-Expression -Command "${Git} clone ${GitUrlPrefix}/${LocalLib}.git ${LocalLib}-${pid} 2>&1"
	Write-Host ${Output}

	If (Test-Path ${LocalLib}-${pid})
	{
		$LocalLibVersion = Get-Content -Path ${LocalLib}-${pid}\configure.ac | select -skip 4 -first 1 | % { $_ -Replace " \[","" } | % { $_ -Replace "\],","" }

		If (Test-Path ${LocalLib})
		{
			Remove-Item -Path ${LocalLib} -Force -Recurse
		}
		New-Item -ItemType directory -Path ${LocalLib} -Force | Out-Null

		If (Test-Path ${LocalLib})
		{
			Copy-Item -Path ${LocalLib}-${pid}\${LocalLib}\*.[chly] -Destination ${LocalLib}\
			Get-Content -Path ${LocalLib}-${pid}\${LocalLib}\${LocalLib}_definitions.h.in | % { $_ -Replace "@VERSION@",${LocalLibVersion} } > ${LocalLib}\${LocalLib}_definitions.h
		}
		Remove-Item -Path ${LocalLib}-${pid} -Force -Recurse

		$NamePrefix = ""

		ForEach (${DirectoryElement} in Get-ChildItem -Path "${LocalLib}\*.l")
		{
			$OutputFile = ${DirectoryElement} -Replace ".l$",".c"

			$NamePrefix = Split-Path -path ${DirectoryElement} -leaf
			$NamePrefix = ${NamePrefix} -Replace "^${LocalLib}_",""
			$NamePrefix = ${NamePrefix} -Replace ".l$","_"

			# PowerShell will raise NativeCommandError if win_flex writes to stdout or stderr
			# therefore 2>&1 is added and the output is stored in a variable.
			$Output = Invoke-Expression -Command "& '${WinFlex}' -Cf ${DirectoryElement} 2>&1"
			Write-Host ${Output}

			# Moving manually sicne win_flex -o <filename> does not provide the expected behavior.
			Move-Item "lex.yy.c" ${OutputFile} -force
		}

		ForEach (${DirectoryElement} in Get-ChildItem -Path "${LocalLib}\*.y")
		{
			$OutputFile = ${DirectoryElement} -Replace ".y$",".c"

			# PowerShell will raise NativeCommandError if win_bison writes to stdout or stderr
			# therefore 2>&1 is added and the output is stored in a variable.
			$Output = Invoke-Expression -Command "& '${WinBison}' -d -v -l -p ${NamePrefix} -o ${OutputFile} ${DirectoryElement} 2>&1"
			Write-Host ${Output}
		}
	}
}

