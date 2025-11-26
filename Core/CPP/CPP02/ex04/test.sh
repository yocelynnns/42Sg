#!/bin/bash

# Compile the program
make

# Check if compilation was successful
if [ ! -f ./sed ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Running tests..."

# Test Case 1: Basic Replacement
echo "hello world, this is a test world." > test1.txt
./sed test1.txt world universe
diff test1.txt.replace <(echo -e "hello universe, this is a test universe.") && echo "✅ Test 1 Passed" || echo "❌ Test 1 Failed"

# Test Case 2: No Occurrences
echo "This text has no matching words." > test2.txt
./sed test2.txt apple banana
diff test2.txt.replace <(echo -e "This text has no matching words.") && echo "✅ Test 2 Passed" || echo "❌ Test 2 Failed"

# Test Case 3: Full Line Replacement
echo "replace this entire line" > test3.txt
./sed test3.txt "replace this entire line" "new content"
diff test3.txt.replace <(echo -e "new content") && echo "✅ Test 3 Passed" || echo "❌ Test 3 Failed"

# Test Case 4: Case Sensitivity
echo "Repeating repeating repeating words repeating." > test4.txt
./sed test4.txt repeating looping
diff test4.txt.replace <(echo -e "Repeating looping looping words looping.") && echo "✅ Test 4 Passed" || echo "❌ Test 4 Failed"

# Test Case 5: Case Insensitivity (Expected to fail if case-sensitive)
echo "HELLO Hello hello HeLLo" > test5.txt
./sed test5.txt hello hi
diff test5.txt.replace <(echo -e "HELLO Hello hi HeLLo") && echo "✅ Test 5 Passed" || echo "❌ Test 5 Failed"

# Test Case 6: Empty File
touch test6.txt
./sed test6.txt anything something
diff test6.txt.replace <(echo -n "") && echo "✅ Test 6 Passed" || echo "❌ Test 6 Failed"

# Test Case 7: Replacement Creates New Matches
echo "abc abcdef abc" > test7.txt
./sed test7.txt abc abcdef
diff test7.txt.replace <(echo -e "abcdef abcdefdef abcdef") && echo "✅ Test 7 Passed" || echo "❌ Test 7 Failed"

# Test Case 8: Special Characters
echo "This & that && these" > test8.txt
./sed test8.txt "&" "and"
diff test8.txt.replace <(echo -e "This and that andand these") && echo "✅ Test 8 Passed" || echo "❌ Test 8 Failed"

# Test Case 9: Multiple Spaces Between Words
echo "hello    world" > test9.txt
./sed test9.txt "hello" "hi"
diff test9.txt.replace <(echo -e "hi    world") && echo "✅ Test 9 Passed" || echo "❌ Test 9 Failed"

# Test Case 10: No Replacement (Word is identical)
echo "replace this with replace" > test10.txt
./sed test10.txt replace replace
diff test10.txt.replace <(echo -e "replace this with replace") && echo "✅ Test 10 Passed" || echo "❌ Test 10 Failed"

# Test Case 11: Replacing with an Empty String
echo "Replace this with nothing." > test11.txt
./sed test11.txt this ""
diff test11.txt.replace <(echo -e "Replace  with nothing.") && echo "✅ Test 11 Passed" || echo "❌ Test 11 Failed"

# Test Case 12: Replacing a Substring in the Middle of a Word
echo "testtesttest" > test12.txt
./sed test12.txt test TEST
diff test12.txt.replace <(echo -e "TESTTESTTEST") && echo "✅ Test 12 Passed" || echo "❌ Test 12 Failed"

# Test Case 13: Single Line with Multiple Occurrences
echo "word word word" > test13.txt
./sed test13.txt word replaced
diff test13.txt.replace <(echo -e "replaced replaced replaced") && echo "✅ Test 13 Passed" || echo "❌ Test 13 Failed"

# Test Case 14: Case Sensitivity - Same Word but Different Case
echo "apple Apple APPLE" > test14.txt
./sed test14.txt apple orange
diff test14.txt.replace <(echo -e "orange Apple APPLE") && echo "✅ Test 14 Passed" || echo "❌ Test 14 Failed"

# Test Case 15: Replacement with Multiple Spaces
echo "Hello   world." > test15.txt
./sed test15.txt "Hello" "Hi"
diff test15.txt.replace <(echo -e "Hi   world.") && echo "✅ Test 15 Passed" || echo "❌ Test 15 Failed"

# Test Case 16: File with Numbers
echo "123 456 789 123" > test16.txt
./sed test16.txt 123 000
diff test16.txt.replace <(echo -e "000 456 789 000") && echo "✅ Test 16 Passed" || echo "❌ Test 16 Failed"

# Test Case 17: Long Word Replaced in Small Word
echo "a little long word" > test17.txt
./sed test17.txt long longlong
diff test17.txt.replace <(echo -e "a little longlong word") && echo "✅ Test 17 Passed" || echo "❌ Test 17 Failed"

# Test Case 18: Multiple Lines with Replacement
echo -e "line 1\nline 2\nline 3" > test18.txt
./sed test18.txt line new
diff test18.txt.replace <(echo -e "new 1\nnew 2\nnew 3") && echo "✅ Test 18 Passed" || echo "❌ Test 18 Failed"

# Test Case 19: Mixed Case Replacement
echo "quick brown fox jumped over lazy dog" > test19.txt
./sed test19.txt fox dog
diff test19.txt.replace <(echo -e "quick brown dog jumped over lazy dog") && echo "✅ Test 19 Passed" || echo "❌ Test 19 Failed"

# Test Case 20: Replacing All
echo "test test test" > test20.txt
./sed test20.txt test TEST
diff test20.txt.replace <(echo -e "TEST TEST TEST") && echo "✅ Test 20 Passed" || echo "❌ Test 20 Failed"

# Cleanup
rm -f test1.txt test1.txt.replace
rm -f test2.txt test2.txt.replace
rm -f test3.txt test3.txt.replace
rm -f test4.txt test4.txt.replace
rm -f test5.txt test5.txt.replace
rm -f test6.txt test6.txt.replace
rm -f test7.txt test7.txt.replace
rm -f test8.txt test8.txt.replace
rm -f test9.txt test9.txt.replace
rm -f test10.txt test10.txt.replace
rm -f test11.txt test11.txt.replace
rm -f test12.txt test12.txt.replace
rm -f test13.txt test13.txt.replace
rm -f test14.txt test14.txt.replace
rm -f test15.txt test15.txt.replace
rm -f test16.txt test16.txt.replace
rm -f test17.txt test17.txt.replace
rm -f test18.txt test18.txt.replace
rm -f test19.txt test19.txt.replace
rm -f test20.txt test20.txt.replace

echo "Tests completed!"

make fclean