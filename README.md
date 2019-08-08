# Sensors, Body, & Motion
Code examples for the NYU Abu Dhabi class IM-UH 3114 Sensors Body & Motion ([Weekly Schedule](http://sbm.nyuad.im/weekly-schedule/)).

Using computer vision, machine learning, gesture recognition, wearable technology, projection mapping, a variety of sensors, and openFrameworks (C++), students will create interactive art and performances that leverage the full potential of the human body. Directly injecting “people-sensing” into an artwork via these readily accessible open source technologies, generates a unique feedback loop, or dialogue-like relationship, where a person and a computer are continuously reacting to each other’s senses. This course will examine this feedback loop, specifically how a person is directly integrated into the artistic expression of the work. Ultimately, students will create interactive installations and performances where the human body is the central component of the artwork.

## Usage


### Initialization (you only need to do these steps once):
If you haven't installed git on your computer, [install git on your computer](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) (or optionally here's [a different set of instructions](https://www.linode.com/docs/development/version-control/how-to-install-git-on-linux-mac-and-windows/)).

Change directory (`cd` on the command line) into the location where you want the class repository to live.

Clone the repo to your computer: `git clone https://github.com/aaronsherwood/sensorsbodymotion.git`

Grab submodules:
* `git submodule init`
* `git submodule update`

Copy all addons in the __oF_addons__ folder in this repo to the actual openFrameworks __addons__ folder.

### Normal Usage:
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

## Browse Generative Design web examples
First `cd` into the Generative Design folder. Then you need to start a local server on your computer:
* python2: `python -m SimpleHTTPServer`
* python3: `python -m http.server`

Once the server is started navigate to `localhost:8000` in your browser.


