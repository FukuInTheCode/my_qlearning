#include "../../includes/my.h"

static void do_episode(my_ql_t *ql, double explo_proba, uint32_t current_state)
{
    for (uint32_t j = 0; j < ql->max_episode_steps; ++j) {
        uint32_t action = my_agent_get_action(ql->agent,\
                                        current_state, explo_proba);
        double old_qv = ql->agent->q_table.arr[current_state][action];
        int next_state = ql->env->action_table.arr[current_state][action];
        if (next_state == -1)
            continue;
        double reward = ql->env->infos_table.arr[next_state][0];
        double max_next_qv = my_matrix_maxrow(&ql->agent->q_table, next_state);
        double new_qv = (1 - ql->alpha) * old_qv + ql->alpha *(reward +\
                                                    ql->gamma * max_next_qv);
        my_agent_set_new_qv(ql->agent, current_state, action, new_qv);
        if (ql->env->infos_table.arr[next_state][1] != 0)
            break;
        current_state = next_state;
    }
}

void my_ql_train(my_ql_t *ql)
{
    uint32_t current_state = ql->env->starting_state;
    double explo_proba = ql->start_explo_proba;
    for (uint32_t i = 0; i < ql->episodes_n; ++i) {
        do_episode(ql, explo_proba, current_state);
        explo_proba = my_max_between(ql->start_explo_proba *\
                    exp(-1 * ql->decay_rate * i), ql->min_explo_proba);
        current_state = ql->env->starting_state;
    }
}
