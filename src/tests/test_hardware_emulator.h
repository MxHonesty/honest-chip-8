//
// Created by Stelian Stoian on 22/12/2020.
//

#ifndef SRC_TEST_HARDWARE_EMULATOR_H
#define SRC_TEST_HARDWARE_EMULATOR_H


class TestHardwareEmulator{
    static void test_load_game_into_memory();  // Tests the load_game_into_memory method.
    static void test_getters_setters();  // Tests the Hardware getters.
public:
    static void run_all_tests();  // Runs all the tests.
};

#endif //SRC_TEST_HARDWARE_EMULATOR_H
