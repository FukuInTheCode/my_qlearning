#include "../includes/my.h"

static void fillMatrix(my_matrix_t *action_table, uint32_t states_n, uint32_t actions_n) {
    int grid_columns = 3;
    int grid_rows = 3;
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



int main(int argc, char* argv[]) {
    srand(69);

    uint32_t states_n = 9;
    uint32_t actions_n = 4;

    uint32_t episodes_n = 1000;
    uint32_t max_episode_steps = 10;

    uint32_t current_state = 0;

    double alpha = 0.1;

    MAT_DECLA(q_table);

    my_matrix_create(states_n, actions_n, 1, &q_table);

    MAT_PRINT(q_table);

    MAT_DECLA(reward_table);

    my_matrix_create(states_n, 1, 1, &reward_table);

    my_matrix_set(&reward_table, 1, 0, -1);
    my_matrix_set(&reward_table, 7, 0, -1);
    my_matrix_set(&reward_table, 8, 0, 1);

    MAT_PRINT(reward_table);
    MAT_DECLA(action_table);

    my_matrix_create(states_n, actions_n, 1, &action_table);
    fillMatrix(&action_table, states_n, actions_n);
    MAT_PRINT(action_table);

    for (uint32_t i = 0; i < episodes_n; ++i) {
        for (uint32_t j = 0; j < max_episode_steps; ++j) {
            uint32_t max_qv = my_matrix_maxrow(q_table, current_state);
            uint32_t max_index = my_matrix_find_col_index(q_table, current_state, max_qv);

        }
    }

    MAT_FREE(q_table);
    MAT_FREE(reward_table);
    MAT_FREE(action_table);

    return 0;
}