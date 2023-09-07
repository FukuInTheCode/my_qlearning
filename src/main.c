#include "../includes/my.h"


int main(int argc, char* argv[]) {
    srand(69);

    uint32_t states_n = 9;
    uint32_t actions_n = 4;

    MAT_DECLA(q_table);

    my_matrix_create(states_n, actions_n, 1, &q_table);

    MAT_PRINT(q_table);

    MAT_DECLA(reward_table);

    my_matrix_create(states_n, 1, 1, &reward_table);
    MAT_PRINT(reward_table);

    MAT_FREE(q_table);
    MAT_FREE(reward_table);

    return 0;
}