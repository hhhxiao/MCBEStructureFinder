//
// Created by xhy on 2021/8/3.
//

#include "be_random.h"
#include <cstdlib>


#define INIT(L, R, OFF) L = 0x6c078965 * ((R) ^ (R >> 30u)) + (OFF)

uint32_t *mt_n_get(uint32_t seed, int n) {
    //uint32_t *head_arr = (uint32_t *) malloc(sizeof(uint32_t) * (n + 1));
    auto *head_arr = new uint32_t[n + 1];
    auto *last_arr = new uint32_t[n + 1];
    auto *result = new uint32_t[n];
    head_arr[0] = seed;
    for (int i = 1; i < n + 1; i++)
        INIT(head_arr[i], head_arr[i - 1], i);
    uint32_t temp = head_arr[n];
    for (int i = n; i < 397; i++)
        INIT(temp, temp, i + 1);
    last_arr[0] = temp;
    for (int i = 1; i < n + 1; ++i)
        INIT(last_arr[i], last_arr[i - 1], i + 397);
    for (int i = 0; i < n; i++) {
        temp = (head_arr[i] & 0x80000000) + (head_arr[i + 1] & 0x7fffffffu);
        head_arr[i] = (temp >> 1u) ^ last_arr[i];
        if (temp % 2 != 0)
            head_arr[i] = head_arr[i] ^ 0x9908b0df;
    }
    for (int i = 0; i < n;
         ++i) {
        uint32_t y = head_arr[i];
        y = y ^ y >> 11u;
        y = y ^ y << 7u & 2636928640u;
        y = y ^ y << 15u & 4022730752u;
        y = y ^ y >> 18u;
        result[i] = y;
    }
    free(head_arr);
    free(last_arr);
    return result;
}

float int_2_float(uint32_t x) {
    return static_cast<float >(x) * 2.328306436538696e-10f;
}