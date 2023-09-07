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

    // set the informations about the env

    // my_g.actions_n = 4;
    // my_g.grid_cols = 4;
    // my_g.grid_rows = 4;

    // my_g.starting_state = 0;

    my_g.actions_n = 4;
    my_g.grid_cols = 6;
    my_g.grid_rows = 6;

    my_g.starting_state = 10;

    AGENT_DECLA(gilbert);

    my_ql_t ql = {
        .episodes_n = 10*1000,
        .max_episode_steps = 11,
        .alpha = 1e-1,
        .decay_rate = 1e-3,
        .gamma = 1e-2 * 99,
        .start_explo_proba = 1.,
        .min_explo_proba = 1e-1
    };

    my_ql_create(&ql, &my_g, &gilbert);

    // set the char repr for the states

    my_matrix_setcol(&(my_g.infos_table), 2, 111);

    // set the reward for a states

    // my_matrix_set(&my_g.infos_table, 11, 0, 10);
    // my_matrix_set(&my_g.infos_table, 6, 0, -1);
    // my_matrix_set(&my_g.infos_table, 7, 0, -1);
    // my_matrix_set(&my_g.infos_table, 4, 0, 10);
    // my_matrix_set(&my_g.infos_table, 12, 0, -10);
    // my_matrix_set(&my_g.infos_table, 10, 0, -1);
    // my_matrix_set(&my_g.infos_table, 8, 0, 1);

    my_matrix_set(&my_g.infos_table, 1, 0, -5);
    my_matrix_set(&my_g.infos_table, 3, 0, 2);
    my_matrix_set(&my_g.infos_table, 7, 0, 8);
    my_matrix_set(&my_g.infos_table, 9, 0, 5);
    my_matrix_set(&my_g.infos_table, 11, 0, 1);
    my_matrix_set(&my_g.infos_table, 12, 0, -10);
    my_matrix_set(&my_g.infos_table, 16, 0, 3);
    my_matrix_set(&my_g.infos_table, 19, 0, -2);
    my_matrix_set(&my_g.infos_table, 23, 0, 6);
    my_matrix_set(&my_g.infos_table, 24, 0, -4);
    my_matrix_set(&my_g.infos_table, 29, 0, 7);
    my_matrix_set(&my_g.infos_table, 31, 0, -6);
    my_matrix_set(&my_g.infos_table, 34, 0, 4);
    my_matrix_set(&my_g.infos_table, 35, 0, -3);
    my_matrix_set(&my_g.infos_table, 40, 0, 9);
    my_matrix_set(&my_g.infos_table, 41, 0, -7);

    fillMatrix(&my_g.action_table, my_g.states_n, my_g.actions_n);
    MAT_PRINT(my_g.infos_table);
    MAT_PRINT(my_g.action_table);

    // my_ql_train(&ql);

    MAT_PRINT(ql.agent->q_table);
    my_env_print_reward(&my_g);
    my_env_print_id(&my_g);

    MAT_FREE(ql.agent->q_table);
    MAT_FREE(ql.env->infos_table);
    MAT_FREE(ql.env->action_table);

    return 0;
}