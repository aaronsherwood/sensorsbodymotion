# Sensors, Body, & Motion
Code examples for the NYU Abu Dhabi [class](http://sbm.nyuad.im/weekly-schedule/).

## Usage

### On the command line:

#### Initialization (you only need to do these steps once)
Clone the repo to your computer: `git clone https://github.com/aaronsherwood/sensorsbodymotion.git`

Grab submodules:
* `git submodule init`
* `git submodule update`

Copy all addons in the __oF_addons__ folder in this repo to the actual openFrameworks __addons__ folder.

#### Working with the repo on your computer
If working off any example, copy that folder and paste it in the __place_your_work_here__ folder to mitigate merge conflicts when new examples are added or old examples are updated. Work only in copies you've put in this folder.

To get new examples: `git pull`

If you're unsure if you've been working in examples directly in the repo you can stash everything before pulling:
* `git stash`
* `git pull`

To get stashed code back: `git stash pop`

To see what's been stashed: `git stash list`

To remove all stashes: `git stash clear`

To reset everything to be just like the repo online:
* `git fetch origin`
* `git reset --hard origin/master`


