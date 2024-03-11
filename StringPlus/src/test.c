#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_example)
{
    ck_assert_int_msg(1, 1);
}
END_TEST

Suite *example_suite_create(void)
{
    Suite *suite = suite_create("Example");
    TCase *tcase_core = tcase_create("Core of example");
    tcase_add_test(tcase_core, test_example);
    suite_add_tcase(suite, tcase_core);
    return suite;
}

int main(void)
{
    Suite *suite = example_suite_create();
    SRunner *suite_runner = srunner_create(suite);
    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// и чо ита?
// яхз
// ...
// кароч создаём тесты, запихиваем их в suite, 
// потом эээ.. кароч яхз, над гуглить

// можн эт тоже разобрать
// #include <check.h>

// Suite *money_suite(void) {
//  Suite *s;
//  TCase *tc_core;

//  s = suite_create("Money"); // Создание тестового набора с именем "Money"
//  tc_core = tcase_create("Core"); // Создание тестового случая с именем "Core"

//  tcase_add_test(tc_core, test_money_create); // Добавление теста в тестовый случай
//  suite_add_tcase(s, tc_core); // Добавление тестового случая в тестовый набор

//  return s;
// }

// int main(void) {
//  int no_failed = 0;
//  Suite *s;
//  SRunner *runner;

//  s = money_suite(); // Создание тестового набора
//  runner = srunner_create(s); // Создание и запуск тестового набора

//  srunner_run_all(runner, CK_NORMAL); // Запуск всех тестовых случаев в тестовом наборе
//  no_failed = srunner_ntests_failed(runner); // Получение количества неудачных тестов
//  srunner_free(runner); // Освобождение ресурсов

//  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
// }
