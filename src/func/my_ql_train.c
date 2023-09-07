#include "../../includes/my.h"

void my_ql_train(my_ql_t *ql)
{
    uint32_t current_state = ql->env->starting_state;
    double exploit_proba = ql->start_explo_proba;
    for (uint32_t i = 0; i < ql->episodes_n; ++i) {
        // reset
        // one episode
        for (uint32_t j = 0; j < ql->max_episode_steps; ++j) {
            // choice the action
            double old_qv;
            uint32_t action;
            if (my_randfloat(0, 1) < exploit_proba) {
                action = my_randint(0, 3);
                old_qv = ql->agent->q_table.arr[current_state][action];
            } else {
                old_qv = my_matrix_maxrow(&ql->agent->q_table, current_state);
                action = my_matrix_find_col_index(&ql->agent->q_table, current_state, old_qv);
            }
            int next_state = ql->env->action_table.arr[current_state][action];
            if (next_state == -1)
                continue;
            // change the ql->agent->q_table based on the reward
            double reward = ql->env->reward_table.arr[next_state][0];
            double max_next_qv = my_matrix_maxrow(&ql->agent->q_table, next_state);
            double new_qv = (1 - ql->alpha) * old_qv + ql->alpha *(reward + ql->gamma * max_next_qv);
            ql->agent->q_table.arr[current_state][action] = new_qv;
            // set the agent
            if (reward != 0 && reward != 1)
                break;
            current_state = next_state;
        }
        exploit_proba = my_max_between(ql->start_explo_proba * exp(-1 * ql->decay_rate * i), ql->min_explo_proba);
        current_state = ql->env->starting_state;
    }
}
