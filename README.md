# Deploy to Glitch from branch

This is a recipe to deploy to [Glitch](https://glitch.com) from a branch that isn't master.

# Instructions

1. Create orphan branch called `glitch` that you can publish to
    ```sh
    git checkout --orphan 
    git reset HEAD -- .  # remove everything from stage
    git add README.md
    git commit -m "Initial commit"
    git push origin glitch
    ```
1. In your GitHub project, go to Settings > Branches and make `glitch` your default branch.
1. In Glitch, go to Advanced Options > Import from GitHub, and enter the name of your project, e.g. `feihong/glitch-deploy-branch`. It should load the files from your `glitch` branch, not `master`.
