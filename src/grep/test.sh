#!/bin/bash

# Удалите файлы, созданные во время тестов
rm -f test.txt test2.txt


echo "test" > test.txt
echo "Test" >> test.txt
echo "other" >> test.txt

./s21_grep "test" test.txt > result.txt
grep "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 1 пройден"
else
  echo "Тест 1 не пройден"
fi

./s21_grep -i "test" test.txt > result.txt
grep -i "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 2 пройден"
else
  echo "Тест 2 не пройден"
fi

./s21_grep -c "test" test.txt > result.txt
grep -c "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 3 пройден"
else
  echo "Тест 3 не пройден"
fi

echo "test" > test2.txt
./s21_grep -l "test" test.txt test2.txt > result.txt
grep -l "test" test.txt test2.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 4 пройден"
else
  echo "Тест 4 не пройден"
fi

./s21_grep -n "test" test.txt > result.txt
grep -n "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 5 пройден"
else
  echo "Тест 5 не пройден"
fi

./s21_grep -v "test" test.txt > result.txt
grep -v "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 6 пройден"
else
  echo "Тест 6 не пройден"
fi

./s21_grep -o "test" test.txt > result.txt
grep -o "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 7 пройден"
else
  echo "Тест 7 не пройден"
fi

echo "test" > test2.txt
./s21_grep -h "test" test.txt test2.txt > result.txt
grep -h "test" test.txt test2.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 8 пройден"
else
  echo "Тест 8 не пройден"
fi

echo "test" > patterns.txt
./s21_grep -f patterns.txt test.txt > result.txt
grep -f patterns.txt test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 9 пройден"
else
  echo "Тест 9 не пройден"
fi

echo "test" > test2.txt
./s21_grep -s "test" test2.txt > result.txt
grep -s "test" test2.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 10 пройден"
else
  echo "Тест 10 не пройден"
fi

./s21_grep -iv "test" test.txt > result.txt
grep -iv "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 11 пройден"
else
  echo "Тест 11 не пройден"
fi

./s21_grep -ic "test" test.txt > result.txt
grep -ic "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 12 пройден"
else
  echo "Тест 12 не пройден"
fi

./s21_grep -in "test" test.txt > result.txt
grep -in "test" test.txt > expected.txt
diff result.txt expected.txt
if [ $? -eq 0 ]; then
  echo "Тест 13 пройден"
else
  echo "Тест 13 не пройден"
fi

#rm -f test.txt test2.txt result.txt expected.txt patterns.txt
