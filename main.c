/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:42 by salhali           #+#    #+#             */
/*   Updated: 2025/07/29 23:23:36 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// minishell/
// ├── main.c               (your current main)
// ├── minishell.h         (your current header)
// ├── execution/
// │   ├── execute.c       (execute_cmds function)
// │   ├── redirections.c  (setup_redirections)
// │   └── path.c          (find_path)
// ├── builtins/
// │   ├── builtin_echo.c
// │   ├── builtin_cd.c
// │   ├── builtin_pwd.c
// │   ├── builtin_export.c
// │   ├── builtin_unset.c
// │   ├── builtin_env.c
// │   └── builtin_exit.c
// ├── parsing/
// │   ├── parser.c        (call_all, typesee, splitit)
// │   ├── tokenizer.c
// │   └── syntax.c        (HardcodeChecks)
// ├── utils/
// │   ├── env_utils.c     (environment functions)
// │   ├── memory.c        (free functions)
// │   └── signals.c       (signal handling)
// └── libft/              (your existing libft)
