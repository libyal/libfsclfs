# Tests C library functions and types.
#
# Version: 20170827

$ExitSuccess = 0
$ExitFailure = 1
$ExitIgnore = 77

$LibraryTests = "block block_descriptor container container_descriptor error io_handle log_range notify owner_page record record_value stream stream_descriptor support"
$LibraryTestsWithInput = "store"

$TestToolDirectory = "..\msvscpp\Release"

Function RunTest
{
	param( [string]$TestType )

	$TestDescription = "Testing: ${TestName}"
	$TestExecutable = "${TestToolDirectory}\fsclfs_test_${TestName}.exe"

	$Output = Invoke-Expression ${TestExecutable}
	$Result = ${LastExitCode}

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	Write-Host "${TestDescription} " -nonewline

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host " (FAIL)"
	}
	Else
	{
		Write-Host " (PASS)"
	}
	Return ${Result}
}

If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\msvscpp\VSDebug"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2010\Release"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2010\VSDebug"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2012\Release"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2012\VSDebug"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2013\Release"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2013\VSDebug"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2015\Release"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2015\VSDebug"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2017\Release"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	$TestToolDirectory = "..\vs2017\VSDebug"
}
If (-Not (Test-Path ${TestToolDirectory}))
{
	Write-Host "Missing test tool directory." -foreground Red

	Exit ${ExitFailure}
}

$Result = ${ExitIgnore}

Foreach (${TestName} in ${LibraryTests} -split " ")
{
	$Result = RunTest ${TestName}

	If (${Result} -ne ${ExitSuccess})
	{
		Break
	}
}

Foreach (${TestName} in ${LibraryTestsWithInput} -split " ")
{
	# TODO: add RunTestWithInput
	$Result = RunTest ${TestName}

	If (${Result} -ne ${ExitSuccess})
	{
		Break
	}
}

Exit ${Result}

