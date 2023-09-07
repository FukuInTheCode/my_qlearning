#include "../includes/my.h"

static void fillMatrix(my_matrix_t *action_table, uint32_t states_n, uint32_t actions_n) {
    int grid_columns = 10;
    int grid_rows = 10;
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

    // my_g.actions_n = 4;
    // my_g.grid_cols = 6;
    // my_g.grid_rows = 6;

    // my_g.starting_state = 10;

    // my_g.actions_n = 4;
    // my_g.grid_cols = 10;
    // my_g.grid_rows = 10;
    // my_g.starting_state = 45;

    my_g.actions_n = 4;
    my_g.grid_cols = 10;
    my_g.grid_rows = 10;

    my_g.starting_state = 16;


    AGENT_DECLA(gilbert);

    my_ql_t ql = {
        .episodes_n = 10*1000,
        .max_episode_steps = 300,
        .alpha = 1e-1,
        .decay_rate = 1e-3,
        .gamma = 1e-2 * 99,
        .start_explo_proba = 1.,
        .min_explo_proba = 1e-1
    };

    my_ql_create(&ql, &my_g, &gilbert);

    printf("%u\n", my_g.states_n);

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

    // my_matrix_set(&my_g.infos_table, 1, 0, -5);
    // my_matrix_set(&my_g.infos_table, 3, 0, 2);
    // my_matrix_set(&my_g.infos_table, 7, 0, 8);
    // my_matrix_set(&my_g.infos_table, 9, 0, 5);
    // my_matrix_set(&my_g.infos_table, 11, 0, 1);
    // my_matrix_set(&my_g.infos_table, 12, 0, -10);
    // my_matrix_set(&my_g.infos_table, 16, 0, 3);
    // my_matrix_set(&my_g.infos_table, 19, 0, -2);
    // my_matrix_set(&my_g.infos_table, 23, 0, 6);
    // my_matrix_set(&my_g.infos_table, 24, 0, -4);
    // my_matrix_set(&my_g.infos_table, 29, 0, 7);
    // my_matrix_set(&my_g.infos_table, 31, 0, -6);
    // my_matrix_set(&my_g.infos_table, 34, 0, 4);
    // my_matrix_set(&my_g.infos_table, 35, 0, -3);
    // my_matrix_set(&my_g.infos_table, 40, 0, 9);
    // my_matrix_set(&my_g.infos_table, 41, 0, -7);

    // my_matrix_set(&my_g.infos_table, 1, 0, -5);
    // my_matrix_set(&my_g.infos_table, 4, 0, 2);
    // my_matrix_set(&my_g.infos_table, 7, 0, 8);
    // my_matrix_set(&my_g.infos_table, 10, 0, 5);
    // my_matrix_set(&my_g.infos_table, 14, 0, 1);
    // my_matrix_set(&my_g.infos_table, 15, 0, -10);
    // my_matrix_set(&my_g.infos_table, 18, 0, 3);
    // my_matrix_set(&my_g.infos_table, 20, 0, -2);
    // my_matrix_set(&my_g.infos_table, 22, 0, 6);
    // my_matrix_set(&my_g.infos_table, 26, 0, -4);
    // my_matrix_set(&my_g.infos_table, 28, 0, 7);
    // my_matrix_set(&my_g.infos_table, 33, 0, -6);
    // my_matrix_set(&my_g.infos_table, 36, 0, 4);
    // my_matrix_set(&my_g.infos_table, 38, 0, -3);
    // my_matrix_set(&my_g.infos_table, 41, 0, 9);
    // my_matrix_set(&my_g.infos_table, 44, 0, -7);
    // my_matrix_set(&my_g.infos_table, 46, 0, -8);
    // my_matrix_set(&my_g.infos_table, 50, 0, -1);
    // my_matrix_set(&my_g.infos_table, 53, 0, 10);
    // my_matrix_set(&my_g.infos_table, 55, 0, -9);
    // my_matrix_set(&my_g.infos_table, 58, 0, 7);
    // my_matrix_set(&my_g.infos_table, 62, 0, -6);
    // my_matrix_set(&my_g.infos_table, 65, 0, 5);
    // my_matrix_set(&my_g.infos_table, 69, 0, -4);
    // my_matrix_set(&my_g.infos_table, 73, 0, 3);
    // my_matrix_set(&my_g.infos_table, 75, 0, -2);
    // my_matrix_set(&my_g.infos_table, 78, 0, 1);
    // my_matrix_set(&my_g.infos_table, 81, 0, -10);
    // my_matrix_set(&my_g.infos_table, 85, 0, 9);
    // my_matrix_set(&my_g.infos_table, 88, 0, -8);
    // my_matrix_set(&my_g.infos_table, 91, 0, -7);
    // my_matrix_set(&my_g.infos_table, 94, 0, 6);

    char mazeLayout[10][10] = {
        {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
        {'W', ' ', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W'},
        {'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W', ' ', 'W'},
        {'W', 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
        {'W', 'W', 'W', 'W', ' ', 'W', 'W', 'W', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', 'W'},
        {'W', 'W', ' ', 'W', ' ', ' ', ' ', 'W', ' ', 'W'},
        {'W', 'W', ' ', 'W', 'W', 'W', 'W', 'W', ' ', 'W'},
        {'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'W', 'W', 'W', ' ', ' ', ' ', 'G'}
    };

    // Initialize the maze using the mazeLayout
    for (int i = 0; i < my_g.grid_rows; i++) {
        for (int j = 0; j < my_g.grid_cols; j++) {
            char cell = mazeLayout[i][j];
            int state = i * my_g.grid_cols + j;
            if (cell == 'W') {
                my_matrix_set(&my_g.infos_table, state, 0, -10); // Set walls to have a negative reward
            } else if (cell == 'G') {
                my_matrix_set(&my_g.infos_table, state, 0, 10);  // Set the goal to have a positive reward
            }
        }
    }
    my_matrix_set(&my_g.infos_table, 99, 1, 1);

    fillMatrix(&my_g.action_table, my_g.states_n, my_g.actions_n);
    MAT_PRINT(my_g.infos_table);
    MAT_PRINT(my_g.action_table);

    my_ql_train(&ql);

    MAT_PRINT(ql.agent->q_table);
    my_env_print_reward(&my_g);
    my_env_print_id(&my_g);

    my_agent_get_path(&gilbert, &my_g, ql.max_episode_steps);

    return 0;
}