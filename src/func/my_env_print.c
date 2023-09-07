#include "../../includes/my.h"

void my_env_print_reward(my_env_t *env)
{
    for (uint32_t i = 0; i < env->grid_rows; ++i) {
        printf("  ");
        for (uint32_t j = 0; j < env->grid_cols; ++j)
            printf("%3.0lf ", env->infos_table.arr[i * env->grid_rows + j][0]);
        printf("\n");
    }
}

void my_env_print_char(my_env_t *env)
{
    for (uint32_t i = 0; i < env->grid_rows; ++i) {
        printf("  ");
        for (uint32_t j = 0; j < env->grid_cols; ++j)
            printf("%c ", (int)(env->infos_table.arr[i * env->grid_rows + j][2]));
        printf("\n");
    }
}

void my_env_print_id(my_env_t *env)
{
    for (uint32_t i = 0; i < env->grid_rows; ++i) {
        printf("  ");
        for (uint32_t j = 0; j < env->grid_cols; ++j)
            printf("%4.u ", env->grid_rows * i + j);
        printf("\n");
    }
}
