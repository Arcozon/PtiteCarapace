/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:36:38 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/22 15:40:54 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	bi_cd(int ac, char **av, int fds[2], t_ms *ms)
{
	(void)ac, (void)av, (void)fds, (void)ms;
	return (0);
}

1 If  no directory operand is given and the HOME environment variable is empty or undefined, the default behavior is imple‐
           mentation-defined and no further steps shall be taken.

        2. If no directory operand is given and the HOME environment variable is set to a non-empty value, the cd utility shall  be‐
           have as if the directory named in the HOME environment variable was specified as the directory operand.

        3. If the directory operand begins with a <slash> character, set curpath to the operand and proceed to step 7.

        4. If the first component of the directory operand is dot or dot-dot, proceed to step 6.

        5. Starting  with the first pathname in the <colon>-separated pathnames of CDPATH (see the ENVIRONMENT VARIABLES section) if
           the pathname is non-null, test if the concatenation of that pathname, a <slash> character if that pathname  did  not  end
           with a <slash> character, and the directory operand names a directory. If the pathname is null, test if the concatenation
           of dot, a <slash> character, and the operand names a directory. In either case, if the resulting string names an existing
           directory, set curpath to that string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH
           until all pathnames have been tested.

        6. Set curpath to the directory operand.enation  of  the  value of PWD, a <slash> character if the value of PWD did not end with a
           <slash> character, and curpath.
