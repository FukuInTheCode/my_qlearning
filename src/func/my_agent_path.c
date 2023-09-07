#include "../../includes/my.h"

void my_agent_get_path(my_agent_t *agent, uint32_t steps,\
                            uint32_t **path, my_matrix_t *actions)
{
    for (uint32_t i = 1; i < steps; ++i) {
        double max = my_matrix_maxrow(&(agent->q_table), (*path)[i - 1]);
        uint32_t id = my_matrix_find_col_index(&(agent->q_table), (*path)[i - 1], max);
        (*path)[i] = actions->arr[(*path)[i - 1]][id];
    }
}
