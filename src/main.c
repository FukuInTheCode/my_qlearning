#include "../includes/my.h"

static void fillMatrix(my_matrix_t *action_table, uint32_t states_n, uint32_t actions_n) {
    int grid_columns = 4;
    int grid_rows = 4;
    for (uint32_t state = 0; state < states_n; state++) {
        for (uint32_t action = 0; action < actions_n; action++) {
            int resulting_state;

            // Calculate the resulting state based on the action and current state
            int current_row = state / grid_columns;
            int current_col = state % grid_columns;

            if (action == 0) {  // "go right"
                if (current_col < grid_columns - 1) {
                    resulting_state = state + 1;
                } else {
                    resulting_state = -1;  // Can't move right if at the right edge
                }
            } else if (action == 1) {  // "go down"
                if (current_row < grid_rows - 1) {
                    resulting_state = state + grid_columns;
                } else {
                    resulting_state = -1;  // Can't move down if at the bottom edge
                }
            } else if (action == 2) {  // "go up"
                if (current_row > 0) {
                    resulting_state = state - grid_columns;
                } else {
                    resulting_state = -1;  // Can't move up if at the top edge
                }
            } else if (action == 3) {  // "go left"
                if (current_col > 0) {
                    resulting_state = state - 1;
                } else {
                    resulting_state = -1;  // Can't move left if at the left edge
                }
            }

            // Assign the resulting state to the matrix
            action_table->arr[state][action] = resulting_state;
        }
    }
}



int main(int argc, char* argv[])
{
    // srand(69);

    // env
    ENV_DECLA(my_g);

    my_g.states_n = 16;
    my_g.actions_n = 4;

    my_g.starting_state = 0;

    my_matrix_set(&my_g.reward_table, 6, 0, -1);
    my_matrix_set(&my_g.reward_table, 7, 0, -1);
    my_matrix_set(&my_g.reward_table, 4, 0, -10);
    my_matrix_set(&my_g.reward_table, 12, 0, -10);
    my_matrix_set(&my_g.reward_table, 10, 0, -1);
    my_matrix_set(&my_g.reward_table, 8, 0, 1);
    my_matrix_set(&my_g.reward_table, 11, 0, 10);

    fillMatrix(&my_g.action_table, my_g.states_n, my_g.actions_n);
    MAT_PRINT(my_g.reward_table);
    MAT_PRINT(my_g.action_table);

    // agent

    AGENT_DECLA(gilbert);

    my_matrix_create(my_g.states_n, my_g.actions_n, 1, &gilbert.q_table);

    // q learning vars

    my_ql_t ql = {
        .env = &my_g,
        .agent = &gilbert,
        .episodes_n = 10*1000,
        .max_episode_steps = 11,
        .alpha = 1e-1,
        .decay_rate = 1e-3,
        .gamma = 1e-2 * 99,
        .start_explo_proba = 1.,
        .min_explo_proba = 1e-1
    };

    // q learning algo
    uint32_t current_state = ql.env->starting_state;
    double exploit_proba = ql.start_explo_proba;
    for (uint32_t i = 0; i < ql.episodes_n; ++i) {
        // reset
        // one episode
        for (uint32_t j = 0; j < ql.max_episode_steps; ++j) {
            // choice the action
            double old_qv;
            uint32_t action;
            if (my_randfloat(0, 1) < exploit_proba) {
                action = my_randint(0, 3);
                old_qv = ql.agent->q_table.arr[current_state][action];
            } else {
                old_qv = my_matrix_maxrow(&ql.agent->q_table, current_state);
                action = my_matrix_find_col_index(&ql.agent->q_table, current_state, old_qv);
            }
            int next_state = ql.env->action_table.arr[current_state][action];
            if (next_state == -1)
                continue;
            // change the ql.agent->q_table based on the reward
            double reward = ql.env->reward_table.arr[next_state][0];
            double max_next_qv = my_matrix_maxrow(&ql.agent->q_table, next_state);
            double new_qv = (1 - ql.alpha) * old_qv + ql.alpha *(reward + ql.gamma * max_next_qv);
            ql.agent->q_table.arr[current_state][action] = new_qv;
            // set the agent
            if (reward != 0 && reward != 1)
                break;
            current_state = next_state;
        }
        exploit_proba = my_max_between(ql.start_explo_proba * exp(-1 * ql.decay_rate * i), ql.min_explo_proba);
        current_state = ql.env->starting_state;
    }

    MAT_PRINT(ql.agent->q_table);

    MAT_FREE(ql.agent->q_table);
    MAT_FREE(ql.env->reward_table);
    MAT_FREE(ql.env->action_table);

    return 0;
}