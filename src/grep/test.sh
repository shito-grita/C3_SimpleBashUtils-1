#!/bin/bash

echo "Testing -e flag..."
output=$(./s21_grep -e "pattern" test.txt)
if [ "$output" = "Pattern found here.
Pattern is here again." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -i flag..."
output=$(./s21_grep -i "Pattern" test.txt)
if [ "$output" = "Pattern found here.
Pattern is here again." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -v flag..."
output=$(./s21_grep -v "pattern" test.txt)
if [ "$output" = "Hello world!
Another line without pattern." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -c flag..."
output=$(./s21_grep -c "pattern" test.txt)
if [ "$output" = "2" ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -l flag..."
output=$(./s21_grep -l "pattern" test1.txt test2.txt)
if [ "$output" = "test1.txt" ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -n flag..."
output=$(./s21_grep -n "pattern" test.txt)
if [ "$output" = "2:Pattern found here.
4:Pattern is here again." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -h flag..."
output=$(./s21_grep -h "pattern" test1.txt test2.txt)
if [ "$output" = "Pattern is in this file." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -s flag..."
output=$(./s21_grep -s "pattern" non_existent_file.txt)
if [ "$output" = "" ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -o flag..."
output=$(./s21_grep -o "pattern" test.txt)
if [ "$output" = "pattern
pattern" ]; then
    echo "passed"
else
    echo "failed"
fi

# Тесты для комбинаций флагов
echo "Testing -iv flags..."
output=$(./s21_grep -iv "Pattern" test.txt)
if [ "$output" = "Hello world!
Another line without pattern." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -ic flags..."
output=$(./s21_grep -ic "Pattern" test.txt)
if [ "$output" = "2" ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -il flags..."
output=$(./s21_grep -il "Pattern" test1.txt test2.txt)
if [ "$output" = "test1.txt" ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -in flags..."
output=$(./s21_grep -in "Pattern" test.txt)
if [ "$output" = "2:Pattern found here.
4:Pattern is here again." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -ih flags..."
output=$(./s21_grep -ih "Pattern" test1.txt test2.txt)
if [ "$output" = "Pattern is in this file." ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -is flags..."
output=$(./s21_grep -is "Pattern" non_existent_file.txt)
if [ "$output" = "" ]; then
    echo "passed"
else
    echo "failed"
fi

echo "Testing -io flags..."
output=$(./s21_grep -io "Pattern" test.txt)
if [ "$output" = "Pattern
Pattern" ]; then
    echo "passed"
else
    echo "failed"
fi
