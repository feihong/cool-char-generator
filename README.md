# Deploy to Glitch from branch

This is a recipe to deploy to [Glitch](https://glitch.com) from a branch that isn't master.

# Create orphan branch called glitch to publish to

```sh
git checkout --orphan glitch
git reset HEAD -- .   # remove all files from stage
git add README.md
git commit -m "Initial commit"
git push origin glitch
```

