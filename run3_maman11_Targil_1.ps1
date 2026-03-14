# Configuration
$MAKEFILE = "Makefile"
$EXECUTABLE = ".\Shani_Peled_remove_blanks.exe"

Clear-Host
Write-Host "--- Testing Report: Shani Peled (Final Robustness Tests) ---" -ForegroundColor Green
Write-Host "----------------------------------------------------------------"

# 1. Compilation Stage
& mingw32-make.exe -f $MAKEFILE clean | Out-Null
& mingw32-make.exe -f $MAKEFILE 2>&1 | Out-Null

if (Test-Path $EXECUTABLE) {
    Write-Host "Compilation: SUCCESS" -ForegroundColor Green
} else {
    Write-Host "Compilation: FAILED" -ForegroundColor Red
    exit
}
Write-Host "----------------------------------------------------------------"

# 2. Bulletproof Test Function
function Run-Test-Advanced {
    param($inputVal, $expected, $num, $testType)
    
    # שליחת הקלט והרצת התוכנית
    $fullOutput = $inputVal | & $EXECUTABLE
    
    # חיפוש מדויק של הכותרת ושליפת השורה שמופיעה מיד אחריה
    $match = $fullOutput | Select-String -Pattern "The string at the end of the function:" -Context 0, 1
    
    if ($match -and $match.Context.PostContext.Count -gt 0) {
        # ניקוי השורה שנשלפה מרווחים עודפים ומירכאות
        $actual = $match.Context.PostContext[0].Trim() -replace '"', ''
    } else {
        $actual = "PARSE_ERROR"
    }

    $status = if ($actual -eq $expected) { "PASS" } else { "FAIL" }
    $color = if ($status -eq "PASS") { "Green" } else { "Red" }

    Write-Host "Test #${num} (${testType}): " -NoNewline; Write-Host $status -ForegroundColor ${color}
    
    # הצגה ברורה של הקלט, גם אם הוא מכיל תווים נסתרים כמו טאב ואנטר
    $displayInput = $inputVal -replace "`t", "\t" -replace "`n", "\n"
    Write-Host "INPUT: '${displayInput}'"
    Write-Host "EXPECTED: '${expected}'"
    Write-Host "ACTUAL: '${actual}'"
    Write-Host "----------------------------------------------------------------"
}

# 3. Running Test Suite
Run-Test-Advanced "aaa bbb ccc" "aaabbbccc" "1" "Standard"
Run-Test-Advanced "  hello  world  " "helloworld" "2" "Spaces at edges"
Run-Test-Advanced "   " "" "3" "Only Spaces"
Run-Test-Advanced "a!@# b$%^ c" "a!@#b$%^c" "4" "Special Characters"
Run-Test-Advanced "TAB`tAND`tNEWLINE`n" "TABANDNEWLINE" "5" "Tabs & Newlines"
Run-Test-Advanced "`t &`n" "&" "6" "Tab, Space, Ampersand, Enter"

Write-Host "End of Comprehensive Report. Ready for Word Document." -ForegroundColor Green