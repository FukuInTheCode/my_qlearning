#include "../../includes/my.h"

void my_env_create(my_env_t *env)
{
    env->states_n = env->grid_cols * env->grid_rows;
    my_matrix_create(env->states_n, 2, 1,\
                            &(env->infos_table));

    my_matrix_create(env->states_n, env->actions_n, 1,\
                                        &(env->action_table));
}
