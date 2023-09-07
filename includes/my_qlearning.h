#ifndef MY_QLEARNING_H
#define MY_QLEARNING_H

#include "my_matrix.h"

typedef struct {
    my_matrix_t q_table;

} my_agent_t;

typedef struct {
    uint32_t states_n;
    uint32_t actions_n;
    my_matrix_t reward_table;
    my_matrix_t action_table;
    uint32_t starting_state;
} my_env_t;

typedef struct {
    my_env_t *env;
    my_agent_t *agent;
    uint32_t episodes_n;
    uint32_t max_episode_steps;
    double gamma;
    double alpha;
    double decay_rate;
    double start_explo_proba;
    double min_explo_proba;
} my_ql_t;

#endif
