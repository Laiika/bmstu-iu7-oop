#include "pairs.h"
#include "points.h"
#include <stdlib.h>

static rc_t pairs_arr_allocate(pairs_t &pairs)
{
    pairs.arr = (pair_t *)malloc(pairs.size * sizeof(pair_t));

    if (NULL == pairs.arr)
        return MEMORY_ERROR;

    return OK;
}

void pairs_free(const pairs_t &pairs)
{
    free(pairs.arr);
}

static rc_t pairs_cnt_read(pairs_t &pairs, FILE *f)
{
    if (1 != fscanf(f, "%d", &pairs.size))
        return INPUT_ERROR;

    if (pairs.size < 1)
        return SIZE_ERROR;

    return OK;
}

static rc_t pair_read(pair_t &pair, FILE *f)
{
    if (2 != fscanf(f, "%d %d", &pair.point1, &pair.point2) || pair.point1 < 0 || pair.point2 < 0 || pair.point1 == pair.point2)
        return INPUT_ERROR;

    return OK;
}

static rc_t pairs_arr_read(pairs_t &pairs, FILE *f)
{
    rc_t rc = OK;

    for (int i = 0; OK == rc && i < pairs.size; i++)
       rc = pair_read(pairs.arr[i], f);

    return rc;
}

rc_t pairs_read(pairs_t &pairs, FILE *f)
{
    rc_t rc = pairs_cnt_read(pairs, f);
    if (OK == rc)
    {
        rc = pairs_arr_allocate(pairs);
        if (OK == rc)
        {
            rc = pairs_arr_read(pairs, f);
            if (rc != OK)
                pairs_free(pairs);
        }
    }

    return rc;
}
