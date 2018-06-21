# Deploy to Glitch from branch

This is a recipe to deploy to [Glitch](https://glitch.com) from a branch that isn't master.

# Create orphan branch to publish to

```sh
git checkout --orphan glitch
git add README.md
git commit -m "Initial commit"
git push origin glitch
```