#include "codexion.h"
void	fifo_enqueue(t_dongle *dongle, t_coder *coder)
{
    dongle->queue[dongle->queue_size] = coder;
	dongle->queue_size++;
}

t_coder	*fifo_dequeue(t_dongle *dongle)
{
    int i;
    i = 0;
    t_coder *firts_coder = dongle->queue[0];
    dongle->queue[0] = NULL;
    while ( i < dongle->queue_size - 1)
    {
        dongle->queue[i] = dongle->queue[i+1];
        i++;
    }
    dongle->queue_size--;
    return (firts_coder);
}

void	edf_enqueue(t_dongle *dongle, t_coder *coder)
{
	long long	deadline;
	int			i;

	deadline = coder->last_compile_start + coder->cfg->time_to_burnout;
	i = 0;
	while (i < dongle->queue_size
		&& dongle->queue[i]->last_compile_start
		+ dongle->queue[i]->cfg->time_to_burnout <= deadline)
		i++;
	while (dongle->queue_size > i)
	{
		dongle->queue[dongle->queue_size]
			= dongle->queue[dongle->queue_size - 1];
		dongle->queue_size--;
	}
	dongle->queue[i] = coder;
	dongle->queue_size++;
}

t_coder	*edf_dequeue(t_dongle *dongle)
{

}
