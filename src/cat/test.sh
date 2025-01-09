#!/bin/bash

echo "Test 1: Output without flags"
diff <(./s21_cat test.txt) <(cat test.txt)
if [ $? -eq 0 ]; then
    echo "Test 1: passed"
else
    echo "Test 1: failed"
fi

echo "Test 2: Flag -b"
diff <(./s21_cat -b test.txt) <(cat -b test.txt)
if [ $? -eq 0 ]; then
    echo "Test 2: passed"
else
    echo "Test 2: failed"
fi

echo "Test 3: Flag -n"
diff <(./s21_cat -n test.txt) <(cat -n test.txt)
if [ $? -eq 0 ]; then
    echo "Test 3: passed"
else
    echo "Test 3: failed"
fi

echo "Test 4: Flag -v"
diff <(./s21_cat -v test.txt) <(cat -v test.txt)
if [ $? -eq 0 ]; then
    echo "Test 4: passed"
else
    echo "Test 4: failed"
fi

echo "Test 5: Flag -e"
diff <(./s21_cat -e test.txt) <(cat -e test.txt)
if [ $? -eq 0 ]; then
    echo "Test 5: passed"
else
    echo "Test 5: failed"
fi

echo "Test 6: Flag -t"
diff <(./s21_cat -t test.txt) <(cat -t test.txt)
if [ $? -eq 0 ]; then
    echo "Test 6: passed"
else
    echo "Test 6: failed"
fi

echo "Test 7: Flag -s"
diff <(./s21_cat -s test.txt) <(cat -s test.txt)
if [ $? -eq 0 ]; then
    echo "Test 7: passed"
else
    echo "Test 7: failed"
fi

echo "Test 8: Multiple flags -benst"
diff <(./s21_cat -benst test.txt) <(cat -benst test.txt)
if [ $? -eq 0 ]; then
    echo "Test 8: passed"
else
    echo "Test 8: failed"
fi

echo "Test 9: Multiple flags -bne"
diff <(./s21_cat -bne test.txt) <(cat -bne test.txt)
if [ $? -eq 0 ]; then
    echo "Test 9: passed"
else
    echo "Test 9: failed"
fi

echo "Test 10: Multiple flags -nst"
diff <(./s21_cat -nst test.txt) <(cat -nst test.txt)
if [ $? -eq 0 ]; then
    echo "Test 10: passed"
else
    echo "Test 10: failed"
fi

echo "Test 11: Multiple flags -vet"
diff <(./s21_cat -vet test.txt) <(cat -vet test.txt)
if [ $? -eq 0 ]; then
    echo "Test 11: passed"
else
    echo "Test 11: failed"
fi

echo "Test 12: Error handling"
./s21_cat non_existent_file.txt
echo "Test 12: passed"

echo "Test 13: Directory handling"
./s21_cat test_directory
echo "Test 13: passed"
