# Git and Github

## Basic Git commands

Check if git is intalled and if installed what version of git is installed.
`git --version`

Configure git after installation : To collaborate we need to identify by adding a username and email id. We do that by using
`git config --global user.name "Jeff Delaney"`
`git config --global user.email "hello@fireship.io"`

If we have an identity already added to the configuration we can check it by using following which will show us our config.
`git config --list`.

* `git init`
* `git status`
* `git add filename` or `git add .` : to add All files
* `git reset .` or `git rm filename` : to remove files from staging area.
* `git commit -m "message"` : -m is for adding message for the commit
* `git commit -am "message"` : -a adds all the tracked file and hence can skip the `git add` if no new files have to be added to tracked files.
* `git log` :  see history of all commits.
* `git remote` : Check all the remote repositories set for your project. For example if you deploy a project that might be a remote(like heroku) and the other can be github.
* `git remote -v` : Get detail links about all remotes.
* `git remote rename currentName toName` : Change the current name of remote.
* `git push` : will push to the default repo and the main branch.
* `git push origin master/main` : push to the origin remote repo and its main/master branch.
* `git fetch` : fetch updated code from remote repositroy. It need to be used with `git branch, git checkout and git reset`.
* `git merge origin/master` : merge code with remote repo.
* `git pull` : is a Git command used to update the local version of a repository from a remote
* `git clone <repo-url> <local-directory>` : clone a remote repo to local directory and optionally change name.

Branches in git :

* `git branch` : list of all branches.
* `git branch branchname` : create a new branch.
* `git branch -d branchname` : delete a branch.
* `git checkout brachname` : move into a branch.
* `git checkout -b branchname` : create and move into a branch.

Changes to Commits

* `git reset <commit-ID>` Rollback to a previous commit but keep the changes in the working directory.
* `git reset <commit-ID> --hard` : Rollback to previous commit and discard all changes.
* `git revert <commit-ID> -m "reverting last commit"` : Undo a commit with a new commit.
* `git commit --amend -m "better message"` : Update the message of previous commit
* `git add <your-file>` then `git commit --amend --no-edit` to add a file that we forgot to add in the previous commit.
* `git log --graph --oneline --decorate` to look at all the commits and branches in a nicer way.

**Git stach** : When we have code that is work in progress and we dont want to commit it yet we can store it in  a stash . Git stash Remove the changes that  are not commited from the current working directory and save them for later use.

* `git stash` : This will create a  stash of current changes.
* `git pop` : Add back the changes to current working directory.
* `git stach save stash-name` : If we want to use multiple stashes we can name the stash and then add particular stash to working directory as needed.
* `git stash list` : list of all stash
* `git stash apply stash-id` : to add the stash to working directory.

Reset code from remote Repo: Lets say we have a remote repo and a local repo and thing are not working on the local repo after some changes were made and we want the code to be reset to the state on the remote repo.

* `git fetch origin` : first step fetch code from remote repo.
* `git reset --hard origin/master` : Then we override the local code with remote code. Note that the local changes will be lost forever.
* `git clean -df` : This will remove all the untracked files form the local repository.

* `git update-git-for-windows` : Update to the lates version of git from windows when git is already installed.

Following two steps can be used to reset to the last commit.

* git reset HEAD --hard : This will undo any changes you've made to tracked files and restore deleted files.
* git clean -fd : This will delete any new files that were added since the last commit. Files that are not tracked due to .gitignore are preserved; they will not be removed. The `f` is for files and `d` is for directories. Using `x` will also delete untracked files, it is not recommended to do it as most times we would not want to do that.

## Intermediate Git

### Perfect Commit

Separate topics while we commit. In the staging area we can add selected files or even parts of files.

We can add parts of the changes done to a file if not all changes made to a given file are for the same topic/concern. We use `git add -p filename.js`. The `-p` flag is used in the case. Now git will take us through the file and we can then command git to add or not to add the part of file with `y | n`.

If we add a part of file the file name will be seen both in staged and non staged files list.

To quickly commit we might add a commit message directly with out commit using the flag `-m` but we want to add a commit message heading as well as describe the commit details in a commit body.

When we use `git commit` once we have staged the files for the commit, it will open out editor and we can write our message heading over there. Then if we add an empty line after the subject we can then add a desciption for the commit. Here we importantly want to add the change but also if there is anything that needs to be watched for in the commit.

### Change tracking for a file

A file that is already been added to be tracked by git cannot be untracked just by later adding it to git ignore.

We need to untrack the file before we add the rule to `.gitignore`.

To do that we use `git rm --cached FileName`.

When we want to untrack a whole directory we will use the `-r` flag for recursive ignore.

`git rm -r --cached <file>`

#### Temprorily untrack files

git [update-index](https://mirrors.edge.kernel.org/pub/software/scm/git/docs/git-update-index.html).

Consider we don't want to  track file for some commits. We can set that file to be `--assume-unchanged` so git will not track the changes to that file in the next commits until we set the file to be tracked for changes again `--no-assume-unchanged`.

`git update-index --assume-unchanged path/to/file`

`git update-index --no-assume-unchanged path/to/file`

### Branching Strategies

WE can different branches for features or development and main branch.

The branches can also be classifed as Long Running and Short-Live branches.

Every project has alteast one Long Running branch, called master or main.

Short_Lived branches are created for a purpose and are reintegrated into a Long Running branch once that purpose is fulfilled. And then the branch can be deleted.

There are two types how git branching strategy can be used.

* GitHub Flow : it is avery simple, very lean, only one long -running branch("main") + feature branches.

* GitFlow : This might offer more structure but also needs to follow a lot more rules.

### Pull Requests

We first create a fork of the repo we would like to contribute to. The Fork maintains a link to the upstream repo so we can pull in future changes from the original repo. Then we clone the forked repo into our local computer.

Once we have the project in our local computer we create new branch, and then move into the branch. We can then make changes to the branch and commit to it. Then we can push the changes to the remote fork by using `git push origin branchname`.

Is used to communicate about and reveiew our code. WE can also use it for contributing code to other repositories that we don't have permissions to.

We can fork the project that we want to contirbute to, then make the changes and make a pull request to the creator of the project to merge your changes to the original project.

Pull Requests are not a core feature of git, but is provided by our remote git repository and hence they might look a little different on different hosts like github or gitlab etc.

### Merge Conflicts

Lets say we wanted to merge develop branch with the main branch. We will use `git merge branch-name`.

When a conflict has occured we can use `git diff` to check the conflict.

WE can undo a conflict and start over by using `git merge --abort` and `git rebase --abort` for respective merge or rebase conflicts.

Solving Conflict can be as simple as cleaning up the file. It can be done by using a GUI or manually by editing the file so that the conflict is resolved.

We can resolve conflict manually by editing the conflict file on the master branch and then creating a merge commit/ or simply a new commit on main branch.

GUI can help in conflict resolve and make it much faster and clear.

### Merge vs Rebase

When **merge** is done git looks at atleast three commits, the ancestor commit(the commit that the branches share), the last commit on the branch being merged and the last commit on the branch in which child branch will be merged.

If there are multiple commits on the main branch git will have to create a commit to merge the branches also called as a merge commit.

Rebase is used to remove branch history and convert the branched structure into a single branch, mostly the main branch.

We have to consider that rebase will rewrite the last commit and also change the parent of the last commit, this might not be good if the code is already pushed to a remote repository that might be used by other developers on  other projects as the parent of the last commit is changed which effectively makes it a different, distinct commit.

We ideally want to use rebase for our local repository before it is pushed onto a remote/shared repository

We use `git rebase branch-name` to rebase a branch into main.

`git rebase master --interactive` Start an interactive rebase from a feature, then choose the squash commend to flatten your commits into a single message.

> Git merge preserves the branch history where as git rebase will club the branches together into one branch as if the development was done on a single branch.

.

> When on github on a project page press `>` to open the project on browser based vs code.
