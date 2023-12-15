#ifndef SHELL_BUILT_IN_SETENV_H
#define SHELL_BUILT_IN_SETENV_H

/**
 * built_in_setenv- Initialize a new environment variable, or modify an existing one
 * Command syntax: setenv VARIABLE VALUE Should print something on stderr on failure
 * @ args: this is paramitar
 * @ env: this is sec paramter
**/

char **built_in_setenv(char **args, char **env);

#endif

