# University of Michigan Human Powered Submarine Team 

## Info
HPS-umich

Electronics Team Lead: 
- Marcellin Barbeau, <mbarbeau@umich.edu>

Team Members: 
- TEMP

README last updated: 5 September 2024

## Task List
### System Tasks
| Task | Timeline |
| ---- | -------- |
| <style>span[class="unchecked"]{color: red;}</style> Make Git repo ----------------------------- | $${\color{blue}Due: 09/08 }$$ |	
| <ul><li>[X] </li></ul> Format Git repo and upload current code --- | $${\color{blue}Due: 09/08 }$$ |	
| <ul><li>[X] </li></ul> Order electronic controls min hardware ---- | $${\color{red }Due: 09/15 }$$ |	
| <ul><li>[X] </li></ul> Code base restructured -------------------- | $${\color{red }Due: 09/15 }$$ |	
| <ul><li>[X] </li></ul> Power system for servos planned ----------- | $${\color{red }Due: 09/08 - 09/22 }$$ |	
| <ul><li>[X] </li></ul> Learn KiCAD ------------------------------- | $${\color{red }Due: 09/08 - 09/22 }$$ |	
| <ul><li>[X] </li></ul> PCB component trade studies --------------- | $${\color{red }Due: 09/08 - 09/22 }$$ |	
| <ul><li>[X] </li></ul> PCB board modeled ------------------------- | $${\color{red }Due: 09/29 }$$ |	
| <style>span[class="checked"]{color: green;}</style> PCB and other hardware ordered | $${\color{red }Due: 10/06}$$ |	

- [ ] dive-code bare-bones runtime ClockManager - $${\color{red }Due: 09/22 }$$	

### Testing Tasks
- [ ] Post processing script planning
- [ ] Sensor calibration test plan written (wet)
- [ ] Servo dry testing
- [ ] Servo wet testing plan
- [ ] Servo wet test


## Git Usage

### Setup Local Git Repository
1. Clone the team repo
```
git clone https://github.com/mbarbeau-umich/HPS-umich.git
```

2. Setup your git account:
```
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
```

3. Pull most up-to-date files
```
git pull
```

4. Make changes on your local branch

5. Push local changes to repo
```
git status 
git add . 
git status
git commit -m "COMMIT_MESSAGE"
git push
```

### Git Branch Commands

List all of the branches in your repository. This is synonymous with git branch --list.
```
git branch
```

Create a new branch called ＜branch＞. This does not check out the new branch.
```
git branch <branch>
```

Rename the current branch to ＜branch＞.
```
git branch -m <branch>
```

Edit in a branch:
```
git checkout <branch>
```

### Useful Git Commands
Delete local changes and pull most recent files
```
git reset --hard origin/main
git pull
```
## Software Loading Hardware

> this section will outline how to boot the hardware with new dive code


## Data formatting

> this section will link to the data file template we will copy for each new mission on the microSD


<!-- 
"/Users/dapperdoctor22/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude" "-C/Users/dapperdoctor22/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega2560 -cwiring "-P/dev/cu.usbmodem143101" -b115200 -Uflash:r:readfile.hex:i

-D "-Uflash:w:/private/var/folders/0t/s_3p0scn1j189ct37h5fk2w00000gn/T/arduino/sketches/5D15626AD9890A31F6F5826A078A8772/sketch_sep8a.ino.hex:i"
 -->