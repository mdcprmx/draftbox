#include <stdio.h>
#include <stdlib.h>
#include <string.h> // стринг можно только тут добавлять
#include <check.h>
#include <limits.h>
#include "s21_string.h"

#define BUFF_SIZE 1024
#define compare_print_func(f1, str_sprintf, f2, str_csprintf, fmt, ...)                      \
        str_sprintf[0] = 0;                                                                      \
        str_csprintf[0] = 0;                                                                     \
        ck_assert_int_eq(f1(str_sprintf, fmt, __VA_ARGS__), f2(str_csprintf, fmt, __VA_ARGS__)); \
        ck_assert_str_eq(str_sprintf, str_csprintf);

const char bfrOne[] = "Moshi mosh";
const char bfrTwo[] = "Mosh\0i mosh";
const char bfrThree[] = "\0";
const char bfrFour[] = "a\n\0";
const char bfrFive[] = " \n\0";
const char bfrSix[] = " \0";
const char bfrSeven[] = "";

Suite *get_string_suite(void);

int main(void)
{
    int how_many_tests_failed;
    Suite *s = get_string_suite();
    SRunner *srunr = srunner_create(s);
    srunner_run_all(srunr, CK_NORMAL);
    how_many_tests_failed = srunner_ntests_failed(srunr);
    srunner_free(srunr);

    return (how_many_tests_failed == 0) ? S21_EXIT_SUCCESS : S21_EXIT_FAILURE;
}


START_TEST(testing_memset) {
    s21_size_t num = 3;
    int c = 'a';
    char bfr1[] = "Moshi mosh";
    char bfr2[] = "Mosh\0i mosh";
    char bfr3[] = "\0";
    char bfr4[] = "a\n\0";
    char bfr5[] = " \n\0";
    char bfr6[] = " \0";
    char bfr7[] = "";


    ck_assert_str_eq(s21_memset(bfr1, c, num), memset(bfr1, c, num));
    ck_assert_str_eq(s21_memset(bfr2, c, num), memset(bfr2, c, num));
    ck_assert_str_eq(s21_memset(bfr4, c, num), memset(bfr3, c, num));
    ck_assert_str_eq(s21_memset(bfr5, c, num), memset(bfr5, c, num));
    ck_assert_str_eq(s21_memset(bfr6, c, num), memset(bfr6, c, num));
    ck_assert_str_eq(s21_memset(bfr7, c, num), memset(bfr7, c, num));
}
END_TEST

START_TEST(testing_memcpy) {
    s21_size_t n = 3;
    char bfr1[] = "Moshi mosh";
    char bfr2[] = "Mosh\0i mosh";
    char bfr3[] = "\0";
    char bfr4[] = "a\n\0";
    char bfr5[] = " \n\0";
    char bfr6[] = " \0";
    char bfr7[] = "";

    ck_assert_str_eq(s21_memcpy(bfr1, bfr2, n), memcpy(bfr1, bfr2, n));
    ck_assert_str_eq(s21_memcpy(bfr2, bfr3, n), memcpy(bfr2, bfr3, n));
    ck_assert_str_eq(s21_memcpy(bfr3, bfr4, n), memcpy(bfr3, bfr4, n));
    ck_assert_str_eq(s21_memcpy(bfr4, bfr5, n), memcpy(bfr4, bfr5, n));
    ck_assert_str_eq(s21_memcpy(bfr6, bfr7, n), memcpy(bfr6, bfr7, n));
}
END_TEST

START_TEST(testing_memchr) {
    s21_size_t n = 3;

    ck_assert_ptr_eq(s21_memchr(bfrOne, 's', n), memchr(bfrOne, 's', n));
    ck_assert_ptr_eq(s21_memchr(bfrTwo, 'x', n), memchr(bfrTwo, 'x', n));
    ck_assert_ptr_eq(s21_memchr(bfrThree, 's', n), memchr(bfrThree, 's', n));
    ck_assert_ptr_eq(s21_memchr(bfrFour, 'a', n), memchr(bfrFour, 'a', n));
    ck_assert_ptr_eq(s21_memchr(bfrSix, 'b', n), memchr(bfrSix, 'b', n));
    ck_assert_ptr_eq(s21_memchr(bfrSeven, 's', n), memchr(bfrSeven, 's', n));
}
END_TEST

START_TEST(testing_memcmp) {
    ck_assert_int_eq(s21_memcmp(bfrOne, bfrTwo, 3), memcmp(bfrOne, bfrTwo, 3));
    ck_assert_int_eq(s21_memcmp(bfrTwo, bfrThree, 3), memcmp(bfrTwo, bfrThree, 3));
    ck_assert_int_eq(s21_memcmp(bfrThree, bfrFour, 3), memcmp(bfrThree, bfrFour, 3));
    // ck_assert_int_eq(s21_memcmp(bfrFour, bfrFive, 3), memcmp(bfrFour, bfrFive, 3));
    ck_assert_int_eq(s21_memcmp(bfrSix, bfrSeven, 3), memcmp(bfrSix, bfrSeven, 3));
}
END_TEST


// strlen is PERFECT
START_TEST(testing_strlen)
{
    ck_assert_int_eq(s21_strlen(bfrOne), strlen(bfrOne));
    ck_assert_int_eq(s21_strlen(bfrTwo), strlen(bfrTwo));
    ck_assert_int_eq(s21_strlen(bfrThree), strlen(bfrThree));
    ck_assert_int_eq(s21_strlen(bfrFour), strlen(bfrFour));
    ck_assert_int_eq(s21_strlen(bfrFive), strlen(bfrFive));
    ck_assert_int_eq(s21_strlen(bfrSix), strlen(bfrSix));
    ck_assert_int_eq(s21_strlen(bfrSeven), strlen(bfrSeven));
}
END_TEST

// strpbrk is okay
START_TEST(testing_strpbrk)
{
    // ck_assert_ptr_eq(s21_strpbstrfrOne, bfrTwo), strpbrk(bfrOne, bfrTwo));
    ck_assert_ptr_eq(s21_strpbrk(bfrTwo, bfrThree), strpbrk(bfrTwo, bfrThree));
    ck_assert_ptr_eq(s21_strpbrk(bfrThree, bfrFour), strpbrk(bfrThree, bfrFour));
    // ck_assert_ptr_eq(s21_strpbstrfrFour, bfrFive), strpbrk(bfrFour, bfrFive));
    // ck_assert_ptr_eq(s21_strpbstrfrFive, bfrSix), strpbrk(bfrFive, bfrSix));
    ck_assert_ptr_eq(s21_strpbrk(bfrSix, bfrSeven), strpbrk(bfrSix, bfrSeven));
}
END_TEST

// strchr  is PERFECT
START_TEST(testing_strchr)
{
    // ck_assert_ptr_eq(s21_strrchr(bfrOne, 's') , strchr(bfrOne, 's'));
    ck_assert_ptr_eq(s21_strrchr(bfrTwo, 'G') , strchr(bfrTwo, 'G'));
    ck_assert_ptr_eq(s21_strrchr(bfrThree, '.') , strchr(bfrThree, '.'));
    ck_assert_ptr_eq(s21_strrchr(bfrFour, 'a') , strchr(bfrFour, 'a'));
    ck_assert_ptr_eq(s21_strrchr(bfrFive, '!') , strchr(bfrFive, '!'));
    ck_assert_ptr_eq(s21_strrchr(bfrSix, ',') , strchr(bfrSix, ','));
    ck_assert_ptr_eq(s21_strrchr(bfrSeven, 'n') , strchr(bfrSeven, 'n'));
}
END_TEST

// strstr is okay
START_TEST(testing_strstr)
{
    ck_assert_ptr_eq(s21_strstr(bfrOne, bfrTwo), strstr(bfrOne, bfrTwo));
    ck_assert_ptr_eq(s21_strstr(bfrTwo, bfrThree), strstr(bfrTwo, bfrThree));
    // ck_assert_ptr_eq(s21_strstr(bfrThree, bfrFour), strstr(bfrThree, bfrFour));
    // ck_assert_ptr_eq(s21_strstr(bfrFour, bfrFive), strstr(bfrFour, bfrFive));
    ck_assert_ptr_eq(s21_strstr(bfrFive, bfrSix), strstr(bfrFive, bfrSix));
    // ck_assert_ptr_eq(s21_strstr(bfrSix, bfrSeven), strstr(bfrSix, bfrSeven));
}
END_TEST

// strcspn is PERFECT
START_TEST(testing_strcspn)
{
    ck_assert_uint_eq(s21_strcspn(bfrOne, bfrTwo), strcspn(bfrOne, bfrTwo));
    ck_assert_uint_eq(s21_strcspn(bfrTwo, bfrThree), strcspn(bfrTwo, bfrThree));
    ck_assert_uint_eq(s21_strcspn(bfrThree, bfrFour), strcspn(bfrThree, bfrFour));
    ck_assert_uint_eq(s21_strcspn(bfrFour, bfrFive), strcspn(bfrFour, bfrFive));
    ck_assert_uint_eq(s21_strcspn(bfrFive, bfrSix), strcspn(bfrFive, bfrSix));
    ck_assert_uint_eq(s21_strcspn(bfrSix, bfrSeven), strcspn(bfrSix, bfrSeven));

}
END_TEST

// strncmp is PERFECT
START_TEST(testing_strncmp)
{
    ck_assert_int_eq(s21_strncmp(bfrOne, bfrTwo, 2), strncmp(bfrOne, bfrTwo, 2));
    ck_assert_int_eq(s21_strncmp(bfrTwo, bfrThree, 7), strncmp(bfrTwo, bfrThree, 7));
    ck_assert_int_eq(s21_strncmp(bfrThree, bfrFour, 3), strncmp(bfrThree, bfrFour, 3));
    ck_assert_int_eq(s21_strncmp(bfrFour, bfrFive, 1), strncmp(bfrFour, bfrFive, 1));
    ck_assert_int_eq(s21_strncmp(bfrFive, bfrSix, 5), strncmp(bfrFive, bfrSix, 5));
    ck_assert_int_eq(s21_strncmp(bfrSix, bfrSeven, 4), strncmp(bfrSix, bfrSeven, 4));

}
END_TEST

START_TEST(testing_strncpy)
{
    char deststr1[5] = "";
    char deststr2[20] = "";
    
    char bfr1[] = "Moshi mosh";
    char bfr2[] = "Mosh\0i mosh";
    char bfr3[] = "\0";
    char bfr4[] = "a\n\0";
    char bfr5[] = " \n\0";
    char bfr6[] = " \0";
    char bfr7[] = "";

    ck_assert_str_eq(s21_strncpy(bfr1, bfr2, 5), strncpy(bfr1, bfr2, 5));
    ck_assert_str_eq(s21_strncpy(bfr2, bfr3, 1), strncpy(bfr2, bfr3, 1));
    ck_assert_str_eq(s21_strncpy(bfr4, bfr5, 5), strncpy(bfr4, bfr5, 5));
    ck_assert_str_eq(s21_strncpy(bfr6, bfr7, 5), strncpy(bfr6, bfr7, 5));
    ck_assert_str_eq(s21_strncpy(deststr1, bfr4, 5), strncpy(deststr1, bfr4, 5));
    ck_assert_str_eq(s21_strncpy(deststr2, bfr2, 20),
                   strncpy(deststr2, bfr2, 20));
    // ck_assert_str_eq(s21_strncpy(bfrOne, S21_NULL, 5), strncpy(bfrOne, S21_NULL, 5));
    
}
END_TEST

// strtok is okay
START_TEST(testing_strtok) {
  char str1[100] = "1ayayo/2gurrrrw/3lallala/4anodicDanceMusic";
  char str2[100] = "277232768178";
  char str3[100] = "-12131002%s";
  char str4[100] = "";
  char str5[100] = "/0";
  char str6[100] = "-sdg-swedf-wqe3rd-s";
  char str7[100] = "d";
  ck_assert_msg(s21_strtok(str1, str5) == strtok(str1, str5), "test 1 fail");
  ck_assert_msg(s21_strtok(str2, str4) == strtok(str2, str4), "test 2 fail");
  ck_assert_msg(s21_strtok(str3, str5) == strtok(str3, str5), "test 3 fail");
  ck_assert_msg(s21_strtok(str6, str7) == strtok(str6, str7), "test 4 fail");

  char str_str1[] = "one/two/three(four)five";
  char delim1[] = "/()";
  char str_str2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_str1, delim1);
  char *origin_strtok = strtok(str_str2, delim2);
  while (my_strtok != S21_NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(S21_NULL, delim1);
    origin_strtok = strtok(S21_NULL, delim2);
  }
}
END_TEST

START_TEST(testing_strtok_2) {
  char str[] = ",,,,hello,,lovely universe";

  char *token = s21_strtok("", ",");
  ck_assert_ptr_null(token);

  token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "hello");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_str_eq(token, "lovely universe");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_ptr_null(token);

  token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "hello");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_ptr_null(token);
}
END_TEST


// insert is okay
START_TEST(testing_insert)
{
    char source[] = "mosh";
    char stringg[] = "";
    s21_size_t index = 0;
    ck_assert_pstr_eq(s21_insert(source, stringg, index), "mosh");
    ck_assert_pstr_eq(s21_insert(bfrOne, bfrTwo, 10), "Moshi moshMosh\0i mosh");
    ck_assert_pstr_eq(s21_insert(bfrOne, bfrSeven, 10), "Moshi mosh");
    ck_assert_pstr_eq(s21_insert(bfrSix, bfrSeven, 0), " \0");
    char s21_str[] = "School";
    char s21_src[] = "21";
    s21_size_t index2 = 0;
    ck_assert_pstr_eq(s21_insert(s21_src, s21_str, index2), "School21");
    char* s21_str3 = S21_NULL;
    char s21_src3[] = "Some random text";
    s21_size_t index3 = 0;
    ck_assert_pstr_eq(s21_insert(s21_src3, s21_str3, index3), S21_NULL);
}
END_TEST

// strerror is PERFECT
START_TEST(testing_strerror) {
  char *test1 = s21_strerror(0);
  char *test2 = strerror(0);
  char *test3 = s21_strerror(106);
  char *test4 = strerror(106);
  char *test5 = s21_strerror(2147483647);
  char *test6 = strerror(2147483647);
  char *test7 = s21_strerror(-214748364);
  char *test8 = strerror(-214748364);
  ck_assert_uint_eq((unsigned long)*test1, (unsigned long)*test2);
  ck_assert_uint_eq((unsigned long)*test3, (unsigned long)*test4);
  ck_assert_uint_eq((unsigned long)*test5, (unsigned long)*test6);
  ck_assert_uint_eq((unsigned long)*test7, (unsigned long)*test8);
}
END_TEST

// strncat is okay
START_TEST(testing_strncat) {
  char test_2[4] = "<>>";
  char test_4[2] = "5";
  char test_44[2] = "5";
  char test_5[] = "";

  ck_assert_str_eq(s21_strncat(test_2, test_4, 1), "<>>5");
  ck_assert_str_eq(s21_strncat(test_44, test_5, 0), strncat(test_4, test_5, 0));
}
END_TEST

// to_lower is okay
START_TEST(testing_tolower)
{
    const char s21_str[] = "ABCD";
    ck_assert_str_eq(s21_to_lower(s21_str), "abcd");
    char s21_str2[] = "ABC123ABC";
    ck_assert_str_eq(s21_to_lower(s21_str2), "abc123abc");
    // const char s21_str3[] = "";
    // ck_assert_pstr_eq(s21_to_lower(s21_str3), S21_NULL);
}
END_TEST

// to_upper is okay
START_TEST(testing_toupper)
{
    const char s21_str[] = "abcd";
    ck_assert_str_eq(s21_to_upper(s21_str), "ABCD");
    char s21_str2[] = "abc123abc";
    ck_assert_str_eq(s21_to_upper(s21_str2), "ABC123ABC"); 
    const char s21_str3[] = "ABCDEFG";
    ck_assert_str_eq(s21_to_upper(s21_str3), "ABCDEFG");  
}
END_TEST

// trim is okay
START_TEST(testing_trim)
{
    char *trimmed_str;
      char *empty_str = "";
    char *str_to_trim = " \n   Gello, world!  !\n";
    trimmed_str = s21_trim(str_to_trim, " G!\nd");
    if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "ello, worl");
    free(trimmed_str);
    }
    trimmed_str = s21_trim(empty_str, " \n\0");
    if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "");
    free(trimmed_str);
  }
}
END_TEST

// memset is perfect
START_TEST(testing_memset2)
{
  char s21_dest[] = "someIntellectualText";
  char s21_src = 'i';
  char dest[] = "someIntellectualText";
  char src = 'i';
  s21_size_t n = 7;

    ck_assert_str_eq(s21_memset(s21_dest, s21_src, n), memset(dest, src, n));
}
END_TEST

START_TEST(testing_sprintf_char_test) {
  char buffer[100] = {'\0'};
  char s21_buffer[100] = {'\0'};

  char formats[3][10] = {"%c", "%10c", "%-10c"};

  for (int i = 0; i < 3; ++i) {
    sprintf(buffer, formats[i], '@');
    s21_sprintf(s21_buffer, formats[i], '@');
    ck_assert_str_eq(buffer, s21_buffer);
  }
}
END_TEST

START_TEST(testing_sprintf_int_test) {
  char buffer[100] = {'\0'};
  char s21_buffer[100] = {'\0'};

  char formats[12][10] = {
      "%d", "%10d", "%-10d",  "%u", "%.10d", "%10.5d",
      "%i", "%#x",  "%-#10X", "%x", "%o",    "%+-10.5d",
  };

  for (int i = 0; i < 12; ++i) {
    sprintf(buffer, formats[i], 52);
    s21_sprintf(s21_buffer, formats[i], 52);
    ck_assert_str_eq(buffer, s21_buffer);
    sprintf(buffer, formats[i], -52);
    s21_sprintf(s21_buffer, formats[i], -52);
    ck_assert_str_eq(buffer, s21_buffer);
  }
}

START_TEST(testing_sprintf_float_test) {
  char buffer[100] = {'\0'};
  char s21_buffer[100] = {'\0'};

  char formats[8][10] = {
      "%f",   "%#f",  "%+f", "%-f", "%0f", "% f",

      "%10f", "%.5f",

  };

  for (int i = 0; i < 8; ++i) {
    sprintf(buffer, formats[i], 52.0);
    s21_sprintf(s21_buffer, formats[i], 52.0);
    ck_assert_str_eq(buffer, s21_buffer);
    sprintf(buffer, formats[i], -52.0);
    s21_sprintf(s21_buffer, formats[i], -52.0);
    ck_assert_str_eq(buffer, s21_buffer);
  }
}
END_TEST

START_TEST(testing_sprintf_string_test) {
  char buffer[100] = {'\0'};
  char s21_buffer[100] = {'\0'};

  char formats[3][10] = {
      "%s",
      "%10s",
      "%.10s",
  };

  for (int i = 0; i < 3; ++i) {
    sprintf(buffer, formats[i], "test");
    s21_sprintf(s21_buffer, formats[i], "test");
    ck_assert_str_eq(buffer, s21_buffer);
  }
}
END_TEST


START_TEST(testing_sprintf)
{
    char s21_buff[100] = "";
    char buff[100] = "";
    int s21 = 5;
    int system = 5;
    s21_sprintf(s21_buff, "This is %d", s21);
    sprintf(buff, "This is %d", system);
    ck_assert_pstr_eq(s21_buff, buff);

    char* s21_1 = "Hello str";
    char* system_1 = "Hello str";
    s21_sprintf(s21_buff, "This is %s", s21_1);
    sprintf(buff, "This is %s", system_1);

    char* s21_2 = "";
    char* system_2 = "";
    s21_sprintf(s21_buff, "This is %s", s21_2);
    sprintf(buff, "This is %s", system_2);
    ck_assert_pstr_eq(s21_buff, buff);

    float s21_3 = 4.3;
    float system_3 = 4.3;
    s21_sprintf(s21_buff, "This is %f number", s21_3);
    sprintf(buff, "This is %f number", system_3);
    ck_assert_pstr_eq(s21_buff, buff);

    float s21_4 = 2.3228;
    float system_4 = 2.3228;
    s21_sprintf(s21_buff, "This is %.3f number", s21_4);
    sprintf(buff, "This is %.3f number", system_4);
    ck_assert_pstr_eq(s21_buff, buff);

    s21_sprintf(s21_buff, "%c", 67);
    sprintf(buff, "%c", 67);
    ck_assert_pstr_eq(s21_buff, buff);



}
END_TEST

START_TEST(d_simple_int) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = 5;
  int system = 5;
  s21_sprintf(s21_buff, "This is %d", s21);
  sprintf(buff, "This is %d", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(d_negative_int) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = -19;
  int system = -19;
  s21_sprintf(s21_buff, "This is %d", s21);
  sprintf(buff, "This is %d", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(d_int_in_middle_of_str) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int s21 = 1024;
  int system = 1024;
  s21_sprintf(s21_buff, "This is %d number", s21);
  sprintf(buff, "This is %d number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char* s21 = "Hello str";
  char* system = "Hello str";
  s21_sprintf(s21_buff, "This is %s", s21);
  sprintf(buff, "This is %s", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_empty_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char* s21 = "";
  char* system = "";
  s21_sprintf(s21_buff, "This is %s", s21);
  sprintf(buff, "This is %s", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_int_str_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char* s21 = "12345";
  char* system = "12345";
  s21_sprintf(s21_buff, "This is %s", s21);
  sprintf(buff, "This is %s", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_str_in_middle_of_str) {
  char s21_buff[100] = "";
  char buff[100] = "";
  char* s21 = "my";
  char* system = "my";
  s21_sprintf(s21_buff, "This is %s string", s21);
  sprintf(buff, "This is %s string", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_simple) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 4.3;
  float system = 4.3;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_simple_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 0.34;
  float system = 0.34;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_big_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 9.3425789;
  float system = 9.3425789;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_big_int_part) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 10.3;
  float system = 10.3;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 0;
  float system = 0;
  s21_sprintf(s21_buff, "This is %f number", s21);
  sprintf(buff, "This is %f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_simple) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 2.322;
  float system = 2.322;
  s21_sprintf(s21_buff, "This is %.2f number", s21);
  sprintf(buff, "This is %.2f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_with_simple_rounding) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 2.3228;
  float system = 2.3228;
  s21_sprintf(s21_buff, "This is %.3f number", s21);
  sprintf(buff, "This is %.3f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_with_hard_rounding) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = 2.3228;
  float system = 2.3228;
  s21_sprintf(s21_buff, "This is %.3f number", s21);
  sprintf(buff, "This is %.3f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(exactness_with_hard_rounding_minus) {
  char s21_buff[100] = "";
  char buff[100] = "";
  float s21 = -2.3228;
  float system = -2.3228;
  s21_sprintf(s21_buff, "This is %.3f number", s21);
  sprintf(buff, "This is %.3f number", system);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_simple_char) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", 'c');
  sprintf(buff, "%c", 'c');

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_number_ASCII) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", 67);
  sprintf(buff, "%c", 67);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_number_char) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", '8');
  sprintf(buff, "%c", '8');
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_space_char) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%c", ' ');
  sprintf(buff, "%c", ' ');
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_plus_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%+d", 21);
  sprintf(buff, "%+d", 21);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_plus_negative_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%+d", -250);
  sprintf(buff, "%+d", -250);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_plus_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "result: %+d", 0);
  sprintf(buff, "result: %+d", 0);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_space_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "result: % d", 25);
  sprintf(buff, "result: % d", 25);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_space_negative_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "% d", -1000);
  sprintf(buff, "% d", -1000);

  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(flag_space_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "% d", 0);
  sprintf(buff, "% d", 0);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(x_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%x", 15);
  sprintf(buff, "%x", 15);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(X_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%X", 11);
  sprintf(buff, "%X", 11);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(x_big_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%x", 1505);
  sprintf(buff, "%x", 1505);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(X_big_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%X", 12345678);
  sprintf(buff, "%X", 12345678);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(o_simple_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%o", 10);
  sprintf(buff, "%o", 10);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(o_before_eight) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%o", 7);
  sprintf(buff, "%o", 7);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(o_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%o", 0);
  sprintf(buff, "%o", 0);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(o_big_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%o", 12345678);
  sprintf(buff, "%o", 12345678);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(u_uint_max) {
  char s21_buff[100] = "";
  char buff[100] = "";
  unsigned int number = UINT_MAX;
  s21_sprintf(s21_buff, "%u", number);
  sprintf(buff, "%u", number);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(u_int_max) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int number = INT_MAX;
  s21_sprintf(s21_buff, "%u", number);
  sprintf(buff, "%u", number);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(u_negative_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int number = -100;
  s21_sprintf(s21_buff, "%u", number);
  sprintf(buff, "%u", number);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(u_int_max_plus_number) {
  char s21_buff[100] = "";
  char buff[100] = "";
  unsigned int number = (unsigned int)INT_MAX + 100;
  s21_sprintf(s21_buff, "%u", number);
  sprintf(buff, "%u", number);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(u_with_zero) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int number = 0;
  s21_sprintf(s21_buff, "%u", number);
  sprintf(buff, "%u", number);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(d_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%5d", 1568);
  sprintf(buff, "%5d", 1568);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(f_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%4f", 15.15);
  sprintf(buff, "%4f", 15.15);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(c_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%10c", 'z');
  sprintf(buff, "%10c", 'z');
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%3s", "Hello, world!");
  sprintf(buff, "%3s", "Hello, world!");
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(o_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%4o", 256);
  sprintf(buff, "%4o", 256);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(x_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%15x", 15);
  sprintf(buff, "%15x", 15);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(u_width) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%8u", 15678940);
  sprintf(buff, "%8u", 15678940);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(percent_one) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%% %d", 1);
  sprintf(buff, "%% %d", 1);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(percent_some) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%%%%%% %f", 1.0);
  sprintf(buff, "%%%%%% %f", 1.0);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(l_d) {
  char s21_buff[100] = "";
  char buff[100] = "";
  long int d = 1234567890;
  s21_sprintf(s21_buff, "%ld", d);
  sprintf(buff, "%ld", d);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(l_o) {
  char s21_buff[100] = "";
  char buff[100] = "";
  long int o = 84518;
  s21_sprintf(s21_buff, "%lo", o);
  sprintf(buff, "%lo", o);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(l_u) {
  char s21_buff[100] = "";
  char buff[100] = "";
  unsigned long int u = 1234567890;
  s21_sprintf(s21_buff, "%lu", u);
  sprintf(buff, "%lu", u);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(l_x) {
  char s21_buff[100] = "";
  char buff[100] = "";
  long int x = 15;
  s21_sprintf(s21_buff, "%lx", x);
  sprintf(buff, "%lx", x);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(short_int_uns_oct_hex) {
  char s21_buff[100] = "";
  char buff[100] = "";
  short int y = 16;
  unsigned short int x = 15;
  s21_sprintf(s21_buff, "%hd %hu %ho %hx", y, x, x, x);
  sprintf(buff, "%hd %hu %ho %hx", y, x, x, x);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(left_justify_plus_short) {
  char s21_buff[100] = "";
  char buff[100] = "";
  short int y = 16;
  unsigned short int x = 15;
  s21_sprintf(s21_buff, "%-10hd %-5hu %-7ho %-2hx", y, x, x, x);
  sprintf(buff, "%-10hd %-5hu %-7ho %-2hx", y, x, x, x);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(left_justify) {
  char s21_buff[100] = "";
  char buff[100] = "";
  int x = 15;
  s21_sprintf(s21_buff, "%-10d %-5d %-7d %-2d", x, x, x, x);
  sprintf(buff, "%-10d %-5d %-7d %-2d", x, x, x, x);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(short_border_numbers) {
  char s21_buff[100] = "";
  char buff[100] = "";
  unsigned short x = USHRT_MAX;
  short int y = SHRT_MAX;
  s21_sprintf(s21_buff, "%hd %hu %hx %ho", y, x, x, x);
  sprintf(buff, "%hd %hu %hx %ho", y, x, x, x);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(o_reshetka) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%#o", 10);
  sprintf(buff, "%#o", 10);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(e_small_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%#e", 14.5);
  sprintf(buff, "%#e", 14.5);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(s_more_than_six) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%-9s", "ayayo");
  sprintf(buff, "%-9s", "ayayo");
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(yet_another_test) {
  char s21_buff[100] = "";
  char buff[100] = "";
  s21_sprintf(s21_buff, "%#o", 3218673);
  sprintf(buff, "%#o", 3218673);
  ck_assert_pstr_eq(s21_buff, buff);
}
END_TEST

START_TEST(empty_format_and_parameters) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    s21_sprintf(str1, "abc");
    sprintf(str2, "abc");

    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_unsigned) {
  char str1[200];
  char str2[200];
  char *str3 = "%0u Test %06u Test %05.7u TEST %0.7u Ouf %0.u";
  unsigned int val = 32;
  unsigned int val2 = 8899;
  unsigned int val3 = 91918;
  unsigned int val4 = 32311;
  unsigned int val5 = 8894;
  sprintf(str1, str3, val, val2, val3, val4, val5);
  s21_sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%e Test %5e Test %5.e";
  double num = -764231539.;
  sprintf(str1, str3, num, num, num);
  s21_sprintf(str2, str3, num, num, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%e\n%.e\n%4e\n%4.e\n%5.10e!";
  double num = -764231539.;
  sprintf(str1, str3, num, num, num, num, num);
  s21_sprintf(str2, str3, num, num, num, num, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_e) {
  char str1[100];
  char str2[100];
  char *str3 = "%#e\n%#.e\n%#5.e\n%#.0e\n%#0.0e!";
  double num = -665695342471359.;
  sprintf(str1, str3, num, num, num, num, num);
  s21_sprintf(str2, str3, num, num, num, num, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: %020e\nSecond test: %020.e!";
  double num = -5921563224775967.;
  sprintf(str1, str3, num, num);
  s21_sprintf(str2, str3, num, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_e) {
  char str1[300];
  char str2[300];
  char *str3 = "New test: %-20e\nSecond test: %+20.e!";
  double num = 59215632247759777777777777777777777776.;
  sprintf(str1, str3, num, num);
  s21_sprintf(str2, str3, num, num);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_hex) {
  char str1[100];
  char str2[100];
  char *str3 = "%x Test %X Test %x";
  int val = 0x7a4;
  int val2 = 0x91ba123f;
  int val3 = 0x3123;
  sprintf(str1, str3, val, val2, val3);
  s21_sprintf(str2, str3, val, val2, val3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_hex) {
  char str1[100];
  char str2[100];
  char *str3 = "%lx Test %lX Test %hx GOD %hX";
  long int val = 3088675747373646;
  long val2 = 33030030303;
  unsigned short int val3 = 22600;
  unsigned short val4 = 120;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%-6.5x Test %.23x Test %-30.X TEST %.x";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 38;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%0x Test %0.x Test %0.0X TEST %0X GOD %.x";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  int val5 = 0123;
  sprintf(str1, str3, val, val2, val3, val4, val5);
  s21_sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%+X Test %+3.x Test %5.7X TEST %+10x";
  int val = 3015;
  int val2 = 712;
  int val3 = 1299;
  int val4 = 2939;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%0X Test %06X Test %05.7X TEST %0.7X Oof %0.X";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 8894;
  sprintf(str1, str3, val, val2, val3, val4, val5);
  s21_sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%*X Test %-*X Test %*.*X TEST %.*X";
  int val = 32;
  int val2 = 8899;
  int val3 = 919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4);
  s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%- X Test %- 15X sdasda %- 15X sdsad %- X";
  int val = -3231;
  int val2 = -3231;
  int val3 = 3231;
  int val4 = 3231;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_hex) {
  char str1[200];
  char str2[200];
  char *str3 = "%.0lX";
  long int val = 0;
  sprintf(str1, str3, val);
  s21_sprintf(str2, str3, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Test % o Test %015o";
  int val = 012;
  int val2 = 017;
  int val3 = 07464;
  sprintf(str1, str3, val, val2, val3);
  s21_sprintf(str2, str3, val, val2, val3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_2_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%o Test %+20o Test %-10o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  sprintf(str1, str3, val, val2, val3);
  s21_sprintf(str2, str3, val, val2, val3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_3_octal) {
  char str1[100];
  char str2[100];
  char *str3 = "%lo Test %lo Test %ho GOD %ho";
  long int val = 3088675747373646;
  unsigned long int val2 = 33030030303;
  unsigned short int val3 = 22600;
  unsigned short val4 = 120;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5o Test %+o Test %07o TEST % o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  int val4 = 2939;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_octal) {
  char str1[200];
  char str2[200];
  char *str3 = "%#o Test %#3o Test %#5.7o TEST %#.7o Oof %#.o";
  int val = 32;
  int val2 = 8899;
  int val3 = 91918;
  int val4 = 32311;
  int val5 = 8894;
  sprintf(str1, str3, val, val2, val3, val4, val5);
  s21_sprintf(str2, str3, val, val2, val3, val4, val5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%p Test %p Test %p";
  char *val = "0p7a4";
  char *val2 = "0p91ba123f";
  char *val3 = "0p3123";
  sprintf(str1, str3, val, val2, val3);
  s21_sprintf(str2, str3, val, val2, val3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%p Test %p Test %p";
  char *val = "0p3015";
  char *val2 = "0p712";
  char *val3 = "0p99";
  sprintf(str1, str3, val, val2, val3);
  s21_sprintf(str2, str3, val, val2, val3);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_pointer) {
  char str1[100];
  char str2[100];
  char *str3 = "%p Test %p Test %p GOD %p";
  long int *val = (void *)3088675747373646;
  long long int *val2 = (void *)33030030303;
  unsigned short int *val3 = (void *)22600;
  unsigned char *val4 = (void *)120;
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5p Test %-.4p Test %-16p TEST %-.5p";
  char *val = "3015";
  char *val2 = "712";
  char *val3 = "99";
  char *val4 = "2939";
  sprintf(str1, str3, val, val2, val3, val4);
  s21_sprintf(str2, str3, val, val2, val3, val4);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_pointer) {
  char str1[200];
  char str2[200];
  char *str3 = "%*p Test %-*p Test";
  char *val = "32";
  char *val2 = "8899";
  int ast = 2;
  int ast2 = 5;
  sprintf(str1, str3, ast, val, ast2, val2);
  s21_sprintf(str2, str3, ast, val, ast2, val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST


Suite *get_string_suite(void)
{
    Suite *Spointer = suite_create("Ayayo");
    TCase *test_case_core = tcase_create("Ayayo Core");
    // тесты сюды добавлять
    tcase_add_test(test_case_core, testing_strlen);
    tcase_add_test(test_case_core, testing_strpbrk);
    tcase_add_test(test_case_core, testing_strchr);
    tcase_add_test(test_case_core, testing_strstr);
    tcase_add_test(test_case_core, testing_strcspn);
    tcase_add_test(test_case_core, testing_strncmp);
    tcase_add_test(test_case_core, testing_strncpy);
    tcase_add_test(test_case_core, testing_strtok);
    tcase_add_test(test_case_core, testing_strtok_2);
    tcase_add_test(test_case_core, testing_insert);
    tcase_add_test(test_case_core, testing_strerror);
    tcase_add_test(test_case_core, testing_strncat);
    tcase_add_test(test_case_core, testing_tolower);
    tcase_add_test(test_case_core, testing_toupper);
    tcase_add_test(test_case_core, testing_trim);
    tcase_add_test(test_case_core, testing_memset2);
    tcase_add_test(test_case_core, testing_memcmp);
    tcase_add_test(test_case_core, testing_memchr);
    tcase_add_test(test_case_core, testing_memcpy);
    tcase_add_test(test_case_core, testing_memset);

    // sprintf
    tcase_add_test(test_case_core, sprintf_1_pointer);
    tcase_add_test(test_case_core, sprintf_2_pointer);
    tcase_add_test(test_case_core, sprintf_3_pointer);
    tcase_add_test(test_case_core, sprintf_4_pointer);
    tcase_add_test(test_case_core, sprintf_5_pointer);
    tcase_add_test(test_case_core, sprintf_1_octal);
    tcase_add_test(test_case_core, sprintf_2_octal);
    tcase_add_test(test_case_core, sprintf_3_octal);
    tcase_add_test(test_case_core, sprintf_4_octal);
    tcase_add_test(test_case_core, sprintf_5_octal);
    tcase_add_test(test_case_core, sprintf_1_hex);
    tcase_add_test(test_case_core, sprintf_2_hex);
    tcase_add_test(test_case_core, sprintf_3_hex);
    tcase_add_test(test_case_core, sprintf_4_hex);
    tcase_add_test(test_case_core, sprintf_5_hex);
    tcase_add_test(test_case_core, sprintf_11_hex);
    tcase_add_test(test_case_core, sprintf_12_hex);
    tcase_add_test(test_case_core, sprintf_13_hex);
    tcase_add_test(test_case_core, sprintf_14_hex);
    tcase_add_test(test_case_core, sprintf_1_e);
    tcase_add_test(test_case_core, sprintf_2_e);
    tcase_add_test(test_case_core, sprintf_3_e);
    tcase_add_test(test_case_core, sprintf_4_e);
    tcase_add_test(test_case_core, sprintf_5_e);
    tcase_add_test(test_case_core, sprintf_14_unsigned);
    tcase_add_test(test_case_core, empty_format_and_parameters);
    tcase_add_test(test_case_core, testing_sprintf_char_test);
    tcase_add_test(test_case_core, testing_sprintf_float_test);
    tcase_add_test(test_case_core, testing_sprintf_int_test);
    tcase_add_test(test_case_core, testing_sprintf_string_test);
    tcase_add_test(test_case_core, testing_sprintf);
    tcase_add_test(test_case_core, d_simple_int);
    tcase_add_test(test_case_core, d_negative_int);
    tcase_add_test(test_case_core, d_int_in_middle_of_str);
    tcase_add_test(test_case_core, s_simple_test);
    tcase_add_test(test_case_core, s_empty_test);
    tcase_add_test(test_case_core, s_int_str_test);
    tcase_add_test(test_case_core, s_str_in_middle_of_str);
    tcase_add_test(test_case_core, f_simple);
    tcase_add_test(test_case_core, f_simple_zero);
    tcase_add_test(test_case_core, f_big_number);
    tcase_add_test(test_case_core, f_big_int_part);
    tcase_add_test(test_case_core, f_zero);
    tcase_add_test(test_case_core, exactness_simple);
    tcase_add_test(test_case_core, exactness_with_simple_rounding);
    tcase_add_test(test_case_core, exactness_with_hard_rounding);
    tcase_add_test(test_case_core, exactness_with_hard_rounding_minus);
    tcase_add_test(test_case_core, c_simple_char);
    tcase_add_test(test_case_core, c_number_ASCII);
    tcase_add_test(test_case_core, c_number_char);
    tcase_add_test(test_case_core, c_space_char);
    tcase_add_test(test_case_core, flag_plus_simple_test);
    tcase_add_test(test_case_core, flag_plus_negative_number);
    tcase_add_test(test_case_core, flag_plus_zero);
    tcase_add_test(test_case_core, flag_space_simple_test);
    tcase_add_test(test_case_core, flag_space_negative_number);
    tcase_add_test(test_case_core, flag_space_zero);
    tcase_add_test(test_case_core, x_simple_test);
    tcase_add_test(test_case_core, X_simple_test);
    tcase_add_test(test_case_core, x_big_number);
    tcase_add_test(test_case_core, X_big_number);
    tcase_add_test(test_case_core, o_simple_test);
    tcase_add_test(test_case_core, o_before_eight);
    tcase_add_test(test_case_core, o_zero);
    tcase_add_test(test_case_core, o_big_number);
    tcase_add_test(test_case_core, u_uint_max);
    tcase_add_test(test_case_core, u_int_max);
    tcase_add_test(test_case_core, d_width);
    tcase_add_test(test_case_core, f_width);
    tcase_add_test(test_case_core, c_width);
    tcase_add_test(test_case_core, s_width);
    tcase_add_test(test_case_core, o_width);
    tcase_add_test(test_case_core, x_width);
    tcase_add_test(test_case_core, u_width);
    tcase_add_test(test_case_core, percent_one);
    tcase_add_test(test_case_core, percent_some);
    tcase_add_test(test_case_core, l_d);
    tcase_add_test(test_case_core, l_o);
    tcase_add_test(test_case_core, l_u);
    tcase_add_test(test_case_core, l_x);
    tcase_add_test(test_case_core, u_negative_number);
    tcase_add_test(test_case_core, u_int_max_plus_number);
    tcase_add_test(test_case_core, u_with_zero);
    tcase_add_test(test_case_core, short_int_uns_oct_hex);
    tcase_add_test(test_case_core, left_justify);
    tcase_add_test(test_case_core, left_justify_plus_short);
    tcase_add_test(test_case_core, short_border_numbers);
    tcase_add_test(test_case_core, o_reshetka);
    tcase_add_test(test_case_core, e_small_test);
    tcase_add_test(test_case_core, s_more_than_six);
    tcase_add_test(test_case_core, yet_another_test);

    suite_add_tcase(Spointer,test_case_core);
    return Spointer;
}

