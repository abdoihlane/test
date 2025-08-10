#ifndef MINISHELL_H
#define MINISHELL_H


#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void ft_free_2d_gc_array(char **arr);
void *ft_malloc(size_t size);
void ft_free_single(void *ptr);  
void ft_free_all(void);
int is_malloc_ptr(void *ptr);
char *ft_strdup1(const char *s);

typedef struct s_save
{
    void *add;
    struct s_save *next;
} t_save;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct t_shell
{
    t_env *envv;
    int last_exit_status;
} t_shell;

#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define COLOR_RESET "\001\033[0m\002"
#define COLOR_PINK "\001\033[38;2;255;105;180m\002"

typedef struct PARSING_STRUCT
{
    int expand_flag;
    int herdoc_flag;
    unsigned int i;
    unsigned int dflag;
    unsigned int qflag;
    unsigned int k;
    int numdollar;
    unsigned int index;
    unsigned int lenofarray;
    char c;
    unsigned int nbofpipes;
    char **content1;
    int nbofcommands;
    char *content;
} t_pars;

typedef struct REDIRECTION_list
{
    char *content;
    int inout;
    struct REDIRECTION_list *next;
} t_red_list;

enum e_token
{
    TOKEN_quotes,
    TOKEN_PIPE,
    TOKEN_WORD,
    TOKEN_REDIRECT_OUTPUT_AM,
    TOKEN_HERDOC,
    TOKEN_REDIRECT_INPUT,
    TOKEN_REDIRECT_OUTPUT
};

typedef struct token_list
{
    enum e_token type;
    struct token_list *next;
    int index;
    char *value;
} t_token;

typedef struct t_cmd
{
    int index;
    int capacity;
    char **array;
    char *cmd;
    int qflag;
    t_red_list *file;
    struct t_cmd *next;
    t_pars *pars;
} t_cmd;

typedef struct words_list
{
    char *content;
    struct words_list *next;
    int index;
} t_wlist;

// Memory management prototypes
t_save **save_add(void);

// Linked list functions
t_wlist *wcreate_node(char *value);
void wlst_addback(t_wlist **lst, t_wlist *node);
int ft_strcmp(char *s1, char *s2);
void init_all(t_pars *p, t_token *t, t_cmd *cmd, t_wlist *w);

// Parsing Functions
void commandornot(t_pars *pars, t_wlist **wlist);
void typesee_plus(t_wlist *list, t_token *new_token);
t_token *typesee(t_wlist **list);
int add_token_node(t_wlist *begin, t_token **tokens, t_token **last, int *index);
int is_quotes(char c);
int is_whitespace(char c);
void skipwhitespaces(t_pars *pars);
int is_redirection(char c);
void count_dollar(t_pars *pars);

t_pars *init_pars(char *in);
void fill_array_plus(t_pars *pars);
void fill_the_array(t_pars *pars, t_shell *shell);
char *fill_array_and_callexpand(t_pars *pars, t_shell *shell);
char *fill_between_space_and_red(t_pars *pars, char *token, t_shell *shell);
t_token *fill_command_fields(t_token *tmp, t_cmd *current);

void print_token(t_token *list);
void free_wlist(t_wlist **list);
void free_plist(t_pars **list);
void free_clist(t_cmd **list);
void free_red_list(t_red_list **list);
void free_token_list(t_token **list);
void free_env_list(t_env **list);
void call_all(char *in, t_wlist **wlist, t_cmd **clist, t_shell *shell);

int check_quotes_closed(char *str);
int red_check(char *str);
int hardcodechecks(char *str);
int check_spaces_and_red(t_pars *pars);
void check_herdoc(char *sa, t_pars *pars);

// Expansion Functions
char *expand_variables(char *input, t_shell *shell);
char *build_result(char *input, char *varname, int var_len, t_shell *shell);
int contains_single_quotes(const char *s);
char *expand_in_quotes(t_pars *pars, char *segment, t_shell *shell);
char *handlequotes(t_pars *pars, char c, t_shell *shell);
char *ft_strjoin_all(char **array);

// Redirection & Command Handling
void handle_red_plus(t_cmd *list, t_token *token);
void handle_redirection(t_cmd *list, t_token *token);

t_cmd *create_new_cmd(int array_size);
int count_cmd_args(t_token *start);
void splitit(t_token *token, t_cmd **final);
void print_cmd_list(t_cmd *cmd);
void reparse_variable(t_pars *pars, t_shell *shell);

// Execution Functions
int builtin_cd(t_cmd *cmd, t_shell *shell);
void update_pwd_variables(t_shell *shell, char *old_pwd);
int handle_cd_error(char *path);
char *get_target_path(t_cmd *cmd, t_shell *shell, char *current_dir);
int get_array_length(char **array);
int is_builtin(t_cmd *command);
int execute_builtin(t_cmd *cmd, t_shell *shell);
void builtin_exit(t_cmd *cmd, t_shell *shell);
int builtin_echo(t_cmd *cmd);
int builtin_pwd(void);
int builtin_export(t_cmd *cmd, t_shell *shell);
int builtin_env(t_cmd *cmd, t_shell *shell);
int builtin_unset(t_cmd *cmd, t_shell *shell);
int builtin_source(t_cmd *cmd);
int is_numeric(const char *str);
void free_test_cmd(t_cmd *cmd);
int count_env_vars(char **env);
char *ft_strcpy(char *dest, const char *src);
char *create_env_string(const char *name, const char *value);
void update_env_variable(t_shell *shell, const char *name, const char *value);
void delete_env_variable(t_shell *shell, const char *name);
char *get_env_value_ll(t_env *env, const char *key);
int ft_strcmp_echo(const char *s);
char **function_split_env(t_shell *shell);
void add_env_node(t_env **head, t_env *new);
char *find_path(char *cmd, char **envp);
void ft_free(char **str);
void free_env(char **env);
void setup_redirections(t_cmd *cmd, t_shell *shell, t_cmd *clist);
void ft_free_2d_array(char **arr);
char *get_env_value(char **env, const char *key);
char **filter_empty_args(t_cmd *cmd);
char **generate_envp_from_envlist(t_shell *shell);
char *ft_strjoin_triple(char *a, char *b, char *c);
int is_valid_var(const char *str);
void sigint_handler(int sig);
void sigint_heredoc(int sig);
int handle_cd_change(char *path, char *current_dir, t_shell *shell);
char *get_cd_path(t_cmd *cmd, t_shell *shell);
int count_non_empty_args(t_cmd *cmd);
void copy_non_empty_args(t_cmd *cmd, char **filtered);
void setup_child_pipes(int in_fd, int *pipe_fd, int has_next);
int handle_builtin_parent(t_cmd *clist, t_shell *shell, int in_fd);
void wait_for_children(pid_t *pids, int count);
void process_single_command(t_cmd **clist, t_shell *shell, char **envp,
    int *in_fd, int *pipe_fd, pid_t *pids, int *i);
void execute_command_loop(t_cmd *clist, t_shell *shell, char **envp);
void handle_append_redirection(t_red_list *tmp);
void handle_output_redirection(t_red_list *tmp);
void handle_input_redirection(t_red_list *tmp);
void handle_heredoc(t_red_list *tmp, t_red_list *head, t_shell *shell, t_cmd *clist);
void WAITPID(pid_t *pids, int i, t_shell *shell);
void execute(t_cmd *clist, t_wlist *wlist, t_shell *shell);
int count_dollars(char *sa);
void split_env(char *equal, t_env *node, char **envp, int i);
t_env *find_env_variable(t_shell *shell, const char *key);
int update_export_variable(t_shell *shell, const char *key, const char *value);
int create_export_variable(t_shell *shell, const char *key, const char *value);
int handle_export_with_value(t_shell *shell, char *arg);
int handle_export_without_value(t_shell *shell, const char *arg);
void signe(void);
t_env *convert_envp_to_envlist(char **envp);
char *search_in_path_dirs(char **directories, char *cmd);
char *check_path_in_directory(char *dir, char *cmd);
char *build_full_path(char *dir, char *cmd);
char *check_direct_path(char *cmd);
int	setup_heredoc_file(void);
char	*process_heredoc_line(char *line, t_shell *shell, t_cmd *clist);
void	write_heredoc_line(int fd, char *expanded);
int	read_heredoc_line(char **line, size_t *len, char *delimiter);
void	cleanup_heredoc(t_red_list *head, char *line, int fd);
void	heredoc_input(char *delimiter, t_red_list *head, t_shell *shell, t_cmd *clist);
void	setup_pipeline(t_cmd *clist, int *pipe_fd);
void	handle_parent_process(int *in_fd, int *pipe_fd, t_cmd *clist);
void	execute_external_command(t_cmd *clist, char **envp);
void	handle_child_process(t_cmd *clist, t_shell *shell, int in_fd, int *pipe_fd);
void	execute_cmds(t_cmd *clist, t_shell *shell);
#endif