# How to contribute:
This is a draft and might change!!
## Getting started

* Make sure you have a [GitHub](https://github.com) account

## Submit changes

* **Don't** create a feature branch on remote rather than create it locally.
  * After you finished you test your issue by integrating it into a local test-branch
    * Pull from develop to get latest changes:
      * Either
      ```bash
      git remote update -p
      git merge @{u}
      ```
      The first command will update all references from remote with your local and -p deletes all local branches
      that have had deleted on remote. 
      * Or
      ```bash
      git pull origin develop
      ```
    * Create the branch:
    ```bash
    git branch integration
    ```
    * Create a patch of your commit against develop:
    ```bash
    git format-patch develop --stdout > patchname.patch
    ```
    * Check if the integration works:
    ```bash
    git checkout integration
    git am < patchname.patch
    ```
  If no errors occured while patching test your changes again and e-mail your changes to us that we can review your
  code and integrate it into develop branch. If we approve your changes you can delete the branch safely by
  ```bash
  git branch -D integration
  ```
  
