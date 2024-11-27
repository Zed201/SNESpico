# temos 4 branchs, main, devG, devM e devJ, enquanto o .yml não funciona para sincronizar elas de forma automática
# ele da merge das branchs de dev na main, se tiver algum confliyo ele aparece para resolver no terminal
# para ter isso funcionando precisa configurar o editor com "git config --global core.editor 'vim'"
# depois de dar merge em todas as branchs na main ele da merge na "direação inversa", atualizando as outras branchs com a main

# Defina a branch principal
main_branch="main"

# Faça checkout na branch principal
git checkout $main_branch

# Atualize a branch principal com o remoto
git pull origin $main_branch


# Liste todas as branches locais (exceto a branch principal)
for branch in $(git branch --format='%(refname:short)' | grep -v "$main_branch"); do
  echo "Fazendo merge da branch $branch na $main_branch..."
  git merge $branch --no-ff
done

# Opcional: Faça push da branch principal após os merges
git push origin $main_branch

for branch in $(git branch --format='%(refname:short)' | grep -v "$main_branch"); do
  echo "Fazendo merge de $main_branch na branch $branch..."
  git checkout $branch
  git merge $main_branch
done
#   git push origin "$branch"

