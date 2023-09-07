#include "../../includes/my_qlearning.h"

void my_agent_create(my_agent_t *agent, uint32_t states_n, uint32_t actions_n)
{
    my_matrix_create(states_n, actions_n, 1, &(agent->q_table));
}

