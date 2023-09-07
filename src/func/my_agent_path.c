#include "../../includes/my.h"

void my_agent_get_path(my_agent_t *agent, my_env_t *env, uint32_t steps)
{
    uint32_t state = env->starting_state;
    printf("%u\n", state);
    for (uint32_t i = 1; i < steps; ++i) {
        double max = my_matrix_maxrow(&(agent->q_table), state);
        uint32_t id = my_matrix_find_col_index(&(agent->q_table), state, max);
        state = env->action_table.arr[state][id];
        printf("%u\n", state);
        if (env->infos_table.arr[state][1] != 0)
            break;
    }
}
