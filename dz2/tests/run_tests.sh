#!/bin/bash
set -e

cd "$(dirname "$0")/.."
clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror main.cpp -o /tmp/fizkat-dz2-test-$$

for test in tests/*.in; do
  expected="${test%.in}.out"
  /tmp/fizkat-dz2-test-$$ < "$test" | diff -u "$expected" -
  echo "OK: $test"
done

rm -f /tmp/fizkat-dz2-test-$$
