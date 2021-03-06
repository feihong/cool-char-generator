# Cool Character Generator

Deployed to: https://cool-char-generator.glitch.me/

This is a simple ReasonReact app that randomly generates visually interesting characters from various writing systems. It makes use of the [Material-UI](https://material-ui.com/) React component library via the [@jsiebern/bs-material-ui](https://github.com/jsiebern/bs-material-ui) bindings.

This project cannot run directly on [Glitch](https://glitch.com) because the Reason toolchain cannot be installed there. However, the compiled JavaScript files can be imported into Glitch by way of a default orphan branch. See the [deploy recipe](DEPLOY.md) for more details.

## Prerequisites

    yarn global add bs-platform
    yarn install

## Scripts

Start the server (only used on Glitch)

    npm start

Run the auto-reloading development server and automatically recompile .re files

    yarn dev

Build

    yarn build

Build for production

    yarn build:production

Run auto-reloading development server

    yarn server

Publish to orphan branch on GitHub

    yarn publish-branch

Clean compiled files and the gh-pages cache

    yarn clean
