#include "../../includes/my.h"

void my_ql_free(my_ql_t *ql)
{
    MAT_FREE(ql->agent->q_table);
    MAT_FREE(ql->env->infos_table);
    MAT_FREE(ql->env->action_table);
}
