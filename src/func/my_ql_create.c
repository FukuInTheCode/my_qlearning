#include "../../includes/my.h"

void my_ql_create(my_ql_t *ql, my_env_t *env, my_agent_t *agent)
{
    ql->env = env;
    ql->agent = agent;
    my_env_create(ql->env);
    my_agent_create(ql->agent, env->states_n, env->actions_n);
}
