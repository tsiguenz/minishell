#include "minishell.h"

int	init_env(t_list **env, char **envp)
{
	t_cmd	tmp;

	if (envp == NULL)
		return (0);
	tmp.args = malloc(2 * sizeof(char));
	if (tmp.args == NULL)
		return (1);
	tmp.args[0] = "exec_name";
	while (*envp)
	{
		tmp.args[1] = *envp;
		msh_export(env, &tmp);
		envp++;
	}
	free(tmp.args);
	return (0);
}

t_list *init(char **envp)
{
	t_list	*result;

	if (set_signal_handler(SIGINT, handle_ctrl_c) \
		|| set_signal_handler(SIGQUIT, NULL))
	{
		puts("error in init");
		return (NULL);
	}
	result = NULL;

	init_env(&result, envp);
	if (update_env(&result, "HOME", getenv("HOME"), ENV_REPLACE_VAR) \
 || update_env(&result, "PATH", getenv("PATH"), ENV_REPLACE_VAR)
		|| update_env(&result, "X", "TEST", ENV_REPLACE_VAR)
		|| update_env(&result, "?", "0", ENV_REPLACE_VAR)
		|| update_env(&result, "PWD", getenv("PWD"), ENV_REPLACE_VAR))
	{
		puts("error initiating msh_env");
		ft_lstclear(&result, free_dict_entry);
		return (NULL);
	}
	return (result);
}
