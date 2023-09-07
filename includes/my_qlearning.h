#ifndef MY_QLEARNING_H
#define MY_QLEARNING_H

#include "my_matrix.h"

#define AGENT_DECLA(nvar) my_agent_t nvar = {.q_table =\
        {.m = 0, .n = 0, .name = #nvar"'s q_table"}, .name = #nvar}

#define ENV_DECLA(nvar) my_env_t nvar = \
    {.states_n = 0, .actions_n = 0, .reward_table =\
                {.m = 0, .n = 0, .name = "Rs of "#nvar}, .action_table =\
                    {.m = 0, .n = 0, .name = "As of "#nvar}, .name = #nvar}

typedef struct {
    char *name;
    my_matrix_t q_table;
} my_agent_t;

typedef struct {
    char *name;
    uint32_t states_n;
    uint32_t actions_n;
    my_matrix_t reward_table;
    my_matrix_t action_table;
    uint32_t starting_state;
    uint32_t grid_cols;
    uint32_t grid_rows;
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

void my_env_create(my_env_t *env);
void my_agent_create(my_agent_t *agent, uint32_t states_n, uint32_t actions_n);
void my_ql_create(my_ql_t *ql, my_env_t *env, my_agent_t *agent);
void my_ql_train(my_ql_t *ql);

#endif
