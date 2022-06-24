**Autor:** Ivan Sedakov
**Email** lazofl24@gmail.com
**Project:** Game Engine for creating 2D Game + The Elder Scrolls 2D: Stories

Information
====
* Qt C++ code for project Game Engine for creating 2D Game

Running
====

1. Run TES2D.exe
2. Enjoy!

Creating own game:
====

* In this GameEngine you can make trivial games correcting files in ./src

* If you want to see your changes in real time, enable "Developer mode" in Main menu

* information about specific folders

	** ./src/panels is used to store Panels components
	
		- in "gameLevels" you can correct and put your own information about story panels
		- in "gameOverPanel" you can correct an information about Game Over panel
		- in "menu" you can find folders for the main menu and menus of levels, manual and settings
		- in "pauseGameLevel" you will be able to make changes in pause panel

	** ./src/GameLevels is used to store Game Levels logic
	
		- in "GameLevels" you can put your own levels (Level_n folder, where n is a number) 
			and cards (q, where q is a number) in levels. There are files for checkpoints, collected items, 
			enemies, ground, main information, player's info and terrain objects.


	** ./src/assets is used to store textures

* information about kinds of sprites of objects
	** spritesAmount is for amount of "SPn" (simple) sprites for walking
	** Shoot, Jump, arrowImage and Strike - according to names



