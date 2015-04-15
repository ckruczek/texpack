# How to contribute:
This is a draft and might change!!
## Getting started

* Make sure you have a [GitHub](https://github.com) account

## Making changes

* commit only related units
* make sure commit messages are in the proper format:
```
Short (50 chars or less) summary of changes

More detailed explanatory text, if necessary.  Wrap it to
about 72 characters or so.  In some contexts, the first
line is treated as the subject of an email and the rest of
the text as the body.  The blank line separating the
summary from the body is critical (unless you omit the body
entirely); tools like rebase can get confused if you run
the two together.

Further paragraphs come after blank lines.

  - Bullet points are okay, too

  - Typically a hyphen or asterisk is used for the bullet,
    preceded by a single space, with blank lines in
    between, but conventions vary here
```

## Submit changes

* **Don't** push to develop or master

* Create an issue branch for each of your changes and base them on develop
  ```bash
  git branch issue_(number) develop
  ```
  * After you finished working on the issue rebase it on integration
    ```bash
    git checkout integration
    
    git pull --ff origin integration
    
    git checkout issue_(number)
    
    git rebase integration
    
    git checkout integration
    
    git merge --ff-only issue_(number)
    ```
* After you finished the integration process, set your issue to review.
* After the reviewed changes are accepted the integration branch will be rebased on develop by the project owner
    
### How to test

* unfortunately there are currently no automated tests, so you need to test your code by hand
* Submit only code that don't have any memory leaks -> check this with valgrind

  If no errors occured while patching test your changes again and e-mail your changes to us that we can review your
  code and integrate it into develop branch. If we approve your changes you can delete the branch safely by
  ```bash
  git branch -D integration
  ```
## Reporting a issue

* Please take a quick look if a related issue already exists
* Write a short title 
* Be as precise as possible and be as considerably as needed
* Assign a label or multiple and a milestone if one related to your topic exists.
  
## Documentation

* Document every method or struct you write, describe parameter and return values as well as the behavior of the 
 method or struct
