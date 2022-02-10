# Git and Github

Basic Git commands

* `git init`
* `git status`
* `git add filename` or `git add .` : to add All files
* `git commit -m "message"` : -m is for adding message for the commit
* `git commit -am "message"` : -a adds all the tracked file and hence can skip the `git add` if no new files have to be added to tracked files.
* `git remote` : Check all the remote repositories set for your project. For example if you deploy a project that might be a remote(like heroku) and the other can be github.

* `git update-git-for-windows` : Update to the lates version of git from windows when git is already installed.

Following two steps can be used to reset to the last commit.

* git reset HEAD --hard : This will undo any changes you've made to tracked files and restore deleted files.
* git clean -fd : This will delete any new files that were added since the last commit. Files that are not tracked due to .gitignore are preserved; they will not be removed. The `f` is for files and `d` is for directories. Using `x` will also delete untracked files, it is not recommended to do it as most times we would not want to do that.

