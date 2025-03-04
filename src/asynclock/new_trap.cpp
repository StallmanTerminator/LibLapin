// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN					\
  "%p func, %d order, %f start, %f duration, %p duration -> %p"

struct bunny_trap		*gl_bunny_trap_head[4];

t_bunny_trap			*bunny_new_trap(t_bunny_trap_function	func,
						t_bunny_call_order	order,
						double			start,
						double			duration,
						void			*param)
{
  struct bunny_trap		**snt;
  struct bunny_trap		*trap;

  if (order == BCO_BEFORE_LOOP_MAIN_FUNCTION)
    snt = &gl_bunny_trap_head[0];
  else
    snt = &gl_bunny_trap_head[2];

  if ((trap = (struct bunny_trap*)bunny_malloc(sizeof(*trap))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "asynclock",
		    func, order, start, duration, param, trap);
  trap->next = NULL;
  trap->prev = NULL;
  trap->remove_it = false;
  trap->start_time = start;
  trap->duration = duration;
  trap->func = func;
  trap->param = param;
  if (snt[0] == NULL)
    {
      snt[0] = trap;
      snt[1] = trap;
    }
  else
    {
      snt[1]->next = trap;
      trap->prev = snt[1];
      snt[1] = trap;
    }
  scream_log_if(PATTERN, "asynclock", func, order, start, duration, param, trap);
  return ((t_bunny_trap*)trap);
}
