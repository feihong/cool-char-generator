# Deploy to Glitch from branch

This is a recipe to deploy to [Glitch](https://glitch.com) from a branch that isn't master. You might find this useful if your project uses a language that compiles to JS, such as ClojureScript, Elm, or ReasonML. In most cases, you cannot install the dev tools for alternative languages on Glitch, but even if you can, it is not worth it because it drastically increases the install and restart times for your project. 

# Instructions

These instructions assume you already created a git repository and committed some files to the master branch.

1. Create orphan branch called `glitch` that you can publish to.
    ```sh
    git checkout --orphan 
    git reset HEAD -- .  # remove everything from stage
    git add README.md
    git commit -m "Initial commit"
    git push origin glitch
    ```
1. In your GitHub project, go to Settings > Branches and make glitch your default branch.
1. In Glitch, go to Advanced Options > Import from GitHub, and enter the name of your project, e.g. `feihong/glitch-deploy-branch`. It should load the files from your glitch branch, not from master.

If the files don't get copied over to the orphan branch as expected, run `yarn gh-pages-clean` to clear the cache files stored in `node_modules/gh-pages/.cache`.