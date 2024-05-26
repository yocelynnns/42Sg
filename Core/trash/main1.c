
/* 
void testFtStrlcpy() {
	clearScreen();
	printf("Function: size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)\n");
	printf("Description: The ft_strlcpy() function copies up to dstsize - 1 characters from the string src to dst, NUL-terminating the result if dstsize is not 0.\n");
	printf("Input: A pointer to the destination string, a pointer to the source string, and the size of the destination buffer\n");
	printf("Output: The total length of the string that would have been copied (not including the NUL character)\n\n");

	// Test case 1: destination buffer size exactly fits the source string
	char dst1[10] = "";
	char src1[] = "hello";
	printf("Test Case 1: dst = \"\", src = \"hello\", dstsize = sizeof(dst1)\n");
	printf("Expected Output: dst = \"hello\", len = 5\n");
	printf("Before: dst = \"%s\"\n", dst1);
	size_t len1 = ft_strlcpy(dst1, src1, sizeof(dst1));
	printf("After: dst = \"%s\", len = %zu\n\n", dst1, len1);

	// Test case 2: destination buffer size smaller than the source string
	char dst2[5] = "";
	char src2[] = "world";
	printf("Test Case 2: dst = \"\", src = \"world\", dstsize = sizeof(dst2)\n");
	printf("Expected Output: dst = \"worl\", len = 5\n");
	printf("Before: dst = \"%s\"\n", dst2);
	size_t len2 = ft_strlcpy(dst2, src2, sizeof(dst2));
	printf("After: dst = \"%s\", len = %zu\n\n", dst2, len2);

	// Test case 3: destination buffer already full
	char dst3[5] = "1234";
	char src3[] = "5678";
	printf("Test Case 3: dst = \"1234\", src = \"5678\", dstsize = sizeof(dst3)\n");
	printf("Expected Output: dst = \"5678\", len = 5\n");
	printf("Before: dst = \"%s\"\n", dst3);
	size_t len3 = ft_strlcpy(dst3, src3, sizeof(dst3));
	printf("After: dst = \"%s\", len = %zu\n\n", dst3, len3);

	// Test case 4: empty source string
	char dst4[10] = "abc";
	char src4[] = "";
	printf("Test Case 4: dst = \"abc\", src = \"\", dstsize = sizeof(dst4)\n");
	printf("Expected Output: dst = \"\", len = 0\n");
	printf("Before: dst = \"%s\"\n", dst4);
	size_t len4 = ft_strlcpy(dst4, src4, sizeof(dst4));
	printf("After: dst = \"%s\", len = %zu\n\n", dst4, len4);

	// Test case 5: NULL pointers
	printf("Test Case 5: NULL pointers\n");
	printf("Expected Output: No change, len = 0\n");
	printf("Before: dst = NULL, src = NULL\n");
	size_t len5 = ft_strlcpy(NULL, NULL, 0);
	printf("After: dst = NULL, src = NULL, len = %zu\n\n", len5);

	// Test case 6: custom strings
	printf("Enter a custom destination string: ");
	char customDst[100];
	scanf(" %99[^\n]", customDst);
	printf("Enter a custom source string: ");
	char customSrc[100];
	scanf(" %99[^\n]", customSrc);
	printf("Enter the size of the destination buffer: ");
	size_t customDstSize;
	scanf("%zu", &customDstSize);
	printf("Before: dst = \"%s\"\n", customDst);
	size_t len6 = ft_strlcpy(customDst, customSrc, customDstSize);
	printf("After: dst = \"%s\", len = %zu\n\n", customDst, len6);
}



int main(void)
{
    // Test cases
    const char str1[] = "Hello, world!";
    const char str2[] = "This is a test string.";
    const char str3[] = "Another example.";

    // Test case 1: Character is in the string
    char *result = ft_strchr(str1, 'o');
    if (result)
        printf("Test 1: Found 'o' in \"%s\" at position: %ld\n", str1, result - str1);
    else
        printf("Test 1: 'o' not found in \"%s\"\n", str1);

    // Test case 2: Character is not in the string
    result = ft_strchr(str1, 'z');
    if (result)
        printf("Test 2: Found 'z' in \"%s\" at position: %ld\n", str1, result - str1);
    else
        printf("Test 2: 'z' not found in \"%s\"\n", str1);

    // Test case 3: Character is the null terminator
    result = ft_strchr(str1, '\0');
    if (result)
        printf("Test 3: Found '\\0' in \"%s\" at position: %ld\n", str1, result - str1);
    else
        printf("Test 3: '\\0' not found in \"%s\"\n", str1);

    // Test case 4: Another string, character present
    result = ft_strchr(str2, 't');
    if (result)
        printf("Test 4: Found 't' in \"%s\" at position: %ld\n", str2, result - str2);
    else
        printf("Test 4: 't' not found in \"%s\"\n", str2);

    // Test case 5: Another string, character not present
    result = ft_strchr(str3, 'x');
    if (result)
        printf("Test 5: Found 'x' in \"%s\" at position: %ld\n", str3, result - str3);
    else
        printf("Test 5: 'x' not found in \"%s\"\n", str3);

    return 0;
}

int main(void) {
    char src[] = "Hello, world!";
    char dst[20];  

    size_t result = strlcpy(dst, src, 5);

    printf("Copied string: %s\n", dst);
    printf("Length of source string: %zu\n", result);

    return 0;
}  */