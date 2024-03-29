char *ft_strjoin(const char *s1, const char *s2)
{
	size_t len_s1 = 0;
	size_t len_s2 = 0;
	size_t i = 0;
	size_t j = 0;
	char *result;

	if (s1)
		while (s1[len_s1])
			len_s1++;
	if (s2)
		while (s2[len_s2])
			len_s2++;
	result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!result)
		return NULL;
	while (i < len_s1)
	{
		result[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

noued_cmd *new_noued_cmd(char *commande, char *redirection)
{
	noued_cmd *nouveau_noeud = (noued_cmd *)malloc(sizeof(noued_cmd));
	if (!nouveau_noeud)
	{
		printf("Erreur d'allocation de mémoire\n");
		exit(EXIT_FAILURE);
	}
	nouveau_noeud->cmd = strdup(commande);
	nouveau_noeud->redirection = (redirection) ? strdup(redirection) : NULL;
	nouveau_noeud->next = NULL;
	return nouveau_noeud;
}

void add_back_noued_cmd(noued_cmd **tete, char *commande, char *redirection)
{
	if (!*tete)
		*tete = new_noued_cmd(commande, redirection);
	else
	{
		noued_cmd *courant = *tete;
		while (courant->next)
			courant = courant->next;
		courant->next = new_noued_cmd(commande, redirection);
	}
}

noued_cmd *split_args_by_pipe(char **args)
{
	noued_cmd *cmd = NULL;
	char *s = NULL;
	char *redirection = NULL;
	int i = 0;

	while (args[i])
	{
		if (strcmp(args[i], "|") == 0)
		{
			add_back_noued_cmd(&cmd, s, redirection);
			free(s);
			s = NULL;
			redirection = NULL;
		}
		else if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0)
		{
			if (args[i + 1])
			{
				redirection = ft_strjoin(args[i], args[i + 1]);
				i++;
			}
			else
			{
				printf("Erreur : Fichier de redirection manquant après l'opérateur.\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (!s)
				s = strdup(args[i]);
			else
			{
				char *temp = ft_strjoin(s, " ");
				free(s);
				s = ft_strjoin(temp, args[i]);
				free(temp);
			}
		}
		i++;
	}
	if (s)
		add_back_noued_cmd(&cmd, s, redirection);
	return cmd;
}

void print_command_list(noued_cmd *head)
{
	noued_cmd *current = head;

	while (current)
	{
		printf("cmd : %s\t\t red : %s\n ", current->cmd, current->redirection);
		current = current->next;
	}
}