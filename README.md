Console based snake application made with C++ using ncurses library

![image](https://user-images.githubusercontent.com/70028851/110622942-0a20d980-8194-11eb-850f-308f7aff39c0.png)


# Functionality

Controls - w = UP, a = LEFT, s = DOWN, d = RIGHT, l = LEAVE

Collision with walls or oneself leads to gameover.

Score increases by 1 when food is eaten.

Speed increases every 10 points.

# How to launch

1. Install the ncurses library.

	Debian/Ubuntu - In the terminal, type the following: 
	sudo apt-get install libncurses5-dev libncursesw5-dev <br> Mac - First install Homebrew (https://brew.sh/). Then, type the following in the terminal: 
	brew install ncurses
  
  You may get the error:<br>
  xcrun: error: invalid active developer path (/Library/Developer/CommandLineTools), missing xcrun at: /Library/Developer/CommandLineTools/usr/bin/xcrun
  
  If so, your xcode command-line tools need to be updated, and this can by done by:
  xcode-select --install

2. In the terminal, navigate to the directory containing the files. Type the following:<br>
    (i) make<br>
    (ii) ./snake
