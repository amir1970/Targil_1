# Configuration
$MAKEFILE = "Makefile"
$EXECUTABLE = ".\Shani_Peled_remove_blanks.exe"

Clear-Host
Write-Host "--- Testing Report: Shani Peled (Including Extreme Edge Cases) ---" -ForegroundColor Green
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

# 2A. Standard Test Function (For valid inputs)
function Run-Test-Advanced {
    param($inputVal, $expected, $num, $testType)
    
    $fullOutput = $inputVal | & $EXECUTABLE
    $match = $fullOutput | Select-String -Pattern "The string at the end of the function:" -Context 0, 1
    
    if ($match -and $match.Context.PostContext.Count -gt 0) {
        $actual = $match.Context.PostContext[0].Trim() -replace '"', ''
    } else {
        $actual = "PARSE_ERROR (Maybe caught by program defense)"
    }

    $status = if ($actual -eq $expected) { "PASS" } else { "FAIL" }
    $color = if ($status -eq "PASS") { "Green" } else { "Red" }

    Write-Host "Test #${num} (${testType}): " -NoNewline; Write-Host $status -ForegroundColor ${color}
    
    $displayInput = $inputVal -replace "`t", "\t" -replace "`n", "\n"
    if ($displayInput.Length -gt 60) { $displayInput = $displayInput.Substring(0, 57) + "..." }
    
    Write-Host "INPUT: '${displayInput}'"
    Write-Host "EXPECTED: '${expected}'"
    Write-Host "ACTUAL: '${actual}'"
    Write-Host "----------------------------------------------------------------"
}

# 2B. Error Test Function (For validating program defense mechanisms)
function Run-Error-Test {
    param($inputVal, $expectedErrorMsg, $num, $testType)
    
    $fullOutput = $inputVal | & $EXECUTABLE
    
    # בודק אם הודעת השגיאה שלכם הודפסה למסך
    $match = $fullOutput | Select-String -Pattern $expectedErrorMsg -SimpleMatch

    if ($match) {
        $status = "PASS"
        $color = "Green"
        $actual = "Program successfully blocked input and printed error."
    } else {
        $status = "FAIL"
        $color = "Red"
        $actual = "Defense failed or wrong error message."
    }

    Write-Host "Test #${num} (${testType}): " -NoNewline; Write-Host $status -ForegroundColor ${color}
    
    $displayInput = $inputVal -replace "`t", "\t" -replace "`n", "\n"
    if ($displayInput.Length -gt 60) { $displayInput = $displayInput.Substring(0, 57) + "..." }

    Write-Host "INPUT: '${displayInput}'"
    Write-Host "EXPECTED ERROR: '${expectedErrorMsg}'"
    Write-Host "ACTUAL BEHAVIOR: '${actual}'"
    Write-Host "----------------------------------------------------------------"
}

# 3. Running Test Suite
# --- Standard & Robustness Tests ---
Run-Test-Advanced "aaa bbb ccc" "aaabbbccc" "1" "Standard"
Run-Test-Advanced "  hello  world  " "helloworld" "2" "Spaces at edges"
Run-Test-Advanced "a!@# b$%^ c" "a!@#b$%^c" "3" "Special Characters"
Run-Test-Advanced "TAB`tAND`tNEWLINE`n" "TABANDNEWLINE" "4" "Tabs & Newlines"
Run-Test-Advanced "`t &`n" "&" "5" "Tab, Space, Ampersand, Enter"

# --- Extreme Edge Cases & Defenses ---
# יצירת מחרוזת חוקית מקסימלית (98 תווים בדיוק)
$maxValid = "A" * 98
Run-Test-Advanced $maxValid $maxValid "6" "Exactly Max Valid Length (98 chars)"

# יצירת מחרוזת שחורגת מהגבול (150 תווים) ובדיקה שהתוכנית חוסמת אותה
$overflowStr = "B" * 150
Run-Error-Test $overflowStr "ERROR: String too long" "7" "Buffer Overflow Attempt (150 chars)"

# בדיקת קלט ריק לחלוטין (רק לחיצה על Enter)
Run-Error-Test "" "ERROR: String is too short" "8" "Empty Input (Only Enter)"

Write-Host "End of Comprehensive Report. Ready for Word Document." -ForegroundColor Green