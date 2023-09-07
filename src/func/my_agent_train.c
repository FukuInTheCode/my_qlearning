#include "../../includes/my.h"

uint32_t my_agent_get_action(my_agent_t *agent, uint32_t current_state,\
                                                    double explo_proba)
{
    if (my_randfloat(0, 1) < explo_proba) {
       return my_randint(0, 3);
    } else {
        double old_qv = my_matrix_maxrow(&(agent->q_table), current_state);
        return my_matrix_find_col_index(&(agent->q_table),\
                                                current_state, old_qv);
    }
}

void my_agent_set_new_qv(my_agent_t *agent, uint32_t current_state,\
                                            uint32_t action, double new_qv)
{
    agent->q_table.arr[current_state][action] = new_qv;
}
