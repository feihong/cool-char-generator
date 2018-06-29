/*

Publish production build to specified orphan branch.

*/
const PUBLISH_BRANCH = 'glitch'

const childProcess = require('child_process')
const fs = require('fs')
const ghpages = require('gh-pages')

function main() {
  childProcess.execSync('yarn build:production')

  // Use rsync to copy files into dist/ folder
  try {
    let cmd = [
      'rsync -av --delete',
      '--exclude=".*"',   // ignore hidden files
      '--exclude=".*/"',  // ignore hidden directories
      '--include "public/bundle.js"',
      '--include "*.bs.js"',
      '--exclude-from .gitignore',
      '.',        // source directory
      'dist',     // destination directory
    ].join(' ')
    console.log(cmd)    
    childProcess.execSync(cmd, {encoding: 'utf-8'})
  } catch (err) {
    console.log(err.stderr)
    return
  }

  // Comment out the devDependencies
  let text = fs.readFileSync('dist/package.json', 'utf-8')
  text = text.replace('"devDependencies":', '"/*devDependencies*/":')
  fs.writeFileSync('dist/package.json', text, 'utf-8')
  
  ghpages.publish('dist', {branch: PUBLISH_BRANCH}, err => console.log(err))
  console.log(`Published production build to ${PUBLISH_BRANCH} branch`)
}

main()
