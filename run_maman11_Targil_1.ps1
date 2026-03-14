# Configuration
$MAKEFILE = "Makefile"
$EXECUTABLE = ".\Shani_Peled_remove_blanks.exe"

Clear-Host
Write-Host "--- Testing Report: Shani Peled ---" -ForegroundColor Green

# 1. Compilation Stage
Write-Host "[DEBUG] Compiling..." -ForegroundColor Gray
& mingw32-make.exe -f $MAKEFILE clean | Out-Null
& mingw32-make.exe -f $MAKEFILE 2>&1 | Out-Null

if (Test-Path $EXECUTABLE) {
    Write-Host "Compilation: SUCCESS" -ForegroundColor Green
} else {
    Write-Host "Compilation: FAILED" -ForegroundColor Red
    exit
}
Write-Host "----------------------------------------"

# 2. Test Function Logic

function Run-Test-Logic {
    param($inputVal, $expected, $num)
    
    # שליחת הקלט לתוכנית וקבלת כל הפלט
    $fullOutput = $inputVal | & $EXECUTABLE
    
    # סינון הודעות המערכת והשארת התוצאה בלבד
    $actual = ($fullOutput | Where-Object { $_ -notmatch "Please enter" -and $_ -ne "" } | Select-Object -Last 1).Trim() -replace '"', ''
    
    # אם המחרוזת מכילה כותרת, ננקה אותה כדי להשוות רק את הערך
    if ($actual -match ":") { $actual = ($actual.Split(":")[1]).Trim() }

    $status = if ($actual -eq $expected) { "PASS" } else { "FAIL" }
    $color = if ($status -eq "PASS") { "Green" } else { "Red" }

    Write-Host "Test #${num}: " -NoNewline; Write-Host $status -ForegroundColor ${color}
    Write-Host "INPUT: ${inputVal}"
    Write-Host "EXPECTED: ${expected}"
    Write-Host "ACTUAL: ${actual}"
    Write-Host "----------------------------------------"
}

# 3. Run Tests (Examples from booklet)
Run-Test-Logic "aaa bbb ccc d e f " "aaabbbcccdef" "1"
Run-Test-Logic "  hello   world  " "helloworld" "2"
Run-Test-Logic "1 2 3 4 5" "12345" "3"

Write-Host "End of Report." -ForegroundColor Green