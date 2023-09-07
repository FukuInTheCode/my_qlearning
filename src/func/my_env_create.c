#include "../../includes/my.h"

void my_env_create(my_env_t *env)
{
    my_matrix_create(env->states_n, 1, 1,\
                            &(env->reward_table));

    my_matrix_create(env->states_n, env->actions_n, 1,\
                                        &(env->action_table));

}
