#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>

# ifndef SIGEMT
#  define SIGEMT -7
# endif

extern int		g_exitcode;
extern pid_t	g_childpid;

typedef struct	s_env
{
	int			argc;
	char		**argv;
	char		**envp;
	size_t		n;
	char		**pathv;
	int			dquote;
	char		**pipe;
}				t_env;

/*
**	main controls (running builtins and commands)
*/
void			ft_countargc(t_env *env);
void			control(t_env *env);
void			my_what_exec(t_env *env);
void			parse_line(t_env *env);
void			ft_runcmd(t_env *env);

/*
**	signals and error handling/printing
*/
void			ft_signal(void);
void			ft_sigprint(int s);
int				ft_issyntaxerror(char *arg);
int				ft_syntaxerrorprint(int ret, char *arg);
void			ft_error(char *cmd, char *arg, char *msg);
void			exit_status(char *line);

/*
**	redirects and pipes handling
*/
int				my_redirect_in(t_env *env);
int				my_redirect_from(t_env *env);
void			run_pipes(t_env *env, int n);

/*
**	commandline split into the argv
*/
char			**ft_splittoargv(char *cmd, char c);
void			ft_freeargv(t_env *env);
void			ft_processargv(t_env *env);
void			ft_processvars(t_env *env, char **res,
								char **arg, char **tmp);

/*
**	builtins: echo, cd, pwd, export, unset, env, exit
*/
void			ft_echo(char **av);
void			ft_cd(t_env *env);
void			ft_pwd(void);
void			ft_export(t_env	*env);
void			ft_unset(t_env *env);
int				is_valid_var_end(char c);
char			*env_get_var(char *var, t_env *env);
void			ft_env(t_env *env);
void			ft_exit(t_env *env);

/*
**	additional for ft_runcmd (running cmds from $PATH)
*/
char			*ft_gethome(t_env *env, char *str);
void			ft_freepathv(t_env *env);
void			ft_getpathv(t_env *env);

/*
**	additional for export builtin
*/
int				u_isvalid(char *line);
int				u_find_var(char *arg, t_env *env);
void			u_sort_and_print(t_env *env);

/*
**	additional for argv brackets processing (redirect symbols handling)
*/
char			*ft_bracketredirs(char *arg);
char			*ft_redirnl(char *arg);
void			ft_argvredirscheck(t_env *env);

#endif
