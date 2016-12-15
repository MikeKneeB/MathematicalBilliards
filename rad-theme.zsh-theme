local ret_status="%(?:%{$fg[green]%}:%{$fg[red]%})"

PROMPT=' %{$fg[cyan]%}%1~%{$reset_color%} %{$fg[yellow]%}[$(ls | wc -l)]%{$reset_color%} ${ret_status}%#%{$reset_color%} '
RPROMPT='%{$fg[cyan]%}%~%{$reset_color%} $(git_prompt_info)%{$fg[magenta]%}%T %D%{$reset_color%}'

ZSH_THEME_GIT_PROMPT_PREFIX="%{$fg_bold[red]%}"
ZSH_THEME_GIT_PROMPT_SUFFIX="%{$reset_color%} "
