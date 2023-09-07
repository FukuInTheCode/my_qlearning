#include "../../includes/my.h"

void my_env_print(my_env_t *env)
{
    for (uint32_t i = 0; i < env->grid_rows; ++i) {
        printf("  ");
        for (uint32_t j = 0; j < env->grid_cols; ++j)
            printf("%lf ", env->infos_table.arr[i * env->grid_rows + j][0]);
        printf("\n");
    }
}
