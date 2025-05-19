t_list *env_to_list(char **envp)
{
	t_list *list = NULL;
	int i = 0;

	while (envp[i])
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return list;
}


void export_var(char *entry, t_shell *shell) //(export nom=valeur)
{
    /*char *equal;
    int name_len;
    char *name ;
    
    equal = ft_strchr(entry, '=');
    if (!equal) 
    {
        printf("Format invalide : %s\n", entry);
        return;
    }

    name_len = equal - entry;
    name = strndup(entry, name_len);

    // Chercher si la variable existe déjà
    
    while (shell->env->content) 
    {
        if (ft_strncmp(shell->env->content, name, name_len) == 0 && 
            (char *)shell->env->content[name_len] == '=') 
        {
            free(shell->env->content);
            shell->env->content = strdup(entry);
            free(name);
            return;
        }
    }*/

    // Ajouter une nouvelle variable
    int count = 0;
    while (shell->env->content) 
    {
        shell->env->next;
        count++;
    }

    char **new_env = malloc(sizeof(char *) * (count + 2));
    for (int i = 0; i < count; i++)
        new_env[i] =shell->env->content;
    new_env[count] = strdup(entry);
    new_env[count + 1] = NULL;

    free(shell->env->content);
    shell->env = new_env;
}

void ft_echo(t_cmd *cmd) 
{
    int i;
    int newline; // par défaut, on met un retour à la ligne

    i = 1;
    newline = 1;
    // Gestion de l'option -n
    if (cmd->argv[1] != NULL && ft_strcmp(cmd->argv[1], "-n") == 0) 
    {
        printf("-n\n");
        newline = 0;
        i = 2; // on commence à afficher à partir du mot suivant
    }
    //printf("%s\n", cmd->argv[i]);
    // Afficher les arguments un à un
    while (cmd->argv[i]) 
    {
        //printf("test1");
        printf("%s", cmd->argv[i]);
        if (cmd->argv[i + 1] != NULL) 
            printf(" "); // espace entre les mots
        i++;
    }
    //printf("\n");
    if (newline) 
        printf("\n");
}


int ft_cd(t_cmd *cmd) 
{
    char cwd[1024];  // Tableau pour stocker le chemin du répertoire courant
    char *str;
    char *tmp;

    if (access(cmd->argv[1], F_OK) != 0)
    {

        if (getcwd(cwd, sizeof(cwd)) == NULL) 
        {
            perror("getcwd() échoué");
            return 1;
        }
        tmp = ft_strjoin(cwd, "/");
        str = ft_strjoin(tmp, cmd->argv[1]);
        free(tmp);
    }
    else
        str = ft_strdup(cmd->argv[1]);
    if (str == NULL) {  // Vérifier que cmd->argv[1] existe
        fprintf(stderr, "cd: argument required\n");
        return 1;
    }
    if (chdir(str) != 0) {  // Changer de répertoire
        perror("cd failed");  // En cas d'erreur
        return 1;
    }
    free(str);
    return 0;
}

int ft_pwd(void)
{
    char cwd[1024];  // Tableau pour stocker le chemin du répertoire courant

    if (getcwd(cwd, sizeof(cwd)) != NULL) 
        printf("%s\n", cwd);  // Affiche le répertoire
    else
        perror("getcwd() échoué");
    return 1;
}

int builtin(t_cmd *cmd)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        ft_cd(cmd);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        ft_echo(cmd);
    return(0);
}