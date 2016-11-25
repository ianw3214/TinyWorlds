# < TINY WORLDS >

## Overview

< TINY WORLDS > is a single player rpg that heavily revolves around story, taking inspiration from 
games like Ori and the blind forest, Bastion, Transistor, and Journey. They main idea of the game 
is playing a character who travels into people's minds/worlds to explore different lives.

The goal of < TINY WORLDS > is to expore different personalities of different people, and deliver
an understanding of the world in the perspective of another person. 

The game is not combat based, but instead revolves around interaction between the player and the 
world objects. The player traverses the world with the arrow keys while using the mouse to click on
objects to interact with them. Throughout the game, the player will jump through worlds of different
people as to see what different personalities there are and the different views of the world. 

There is no progression in terms of leveling up or gaining strength. Instead, the sense of progression 
is achieved through personal growth by moving through worlds and understanding the views of different 
people. 

The stories will be conveyed through the in game interactions, and there will be minimal text and
cutscenes. The player be able to understand the story with minimal effort.

## Environment

Each world has a dream like quality to simulate a world within a person. Depending on the person, the
world will be populated with different creatures. Worlds can vary in how similar they are to reality, 
and transitions can be drastic between worlds. The goal is to take the persons thoughts and translate
it into the game world that the player is exploring. 

There is a 'core' to every world, something that represents the main idea of the persons thoughts. These
can be good, bad, or neutral, like wisdom or greed. The elements of the world will loosley relate to 
the core. 

Most elements of the world will be natural with some elements of fantasy constructed of mostly organic
shapes. In some rare cases, the persons thoughts will be very modern and the world will therefore feel
very industrial and flat. These worlds will have less organic shapes and instead be constructed of sharp
edges and well defined structures. 

Every world has a dark side that represents the persons fears, which is up to the character to face. Some
fears may require the player to fight it, but others may require the player to aid it. Every fear in 
every world will be different, some more extreme than others. 

For details of each world, see the [world design document](https://github.com/ianw3214/TinyWorlds/blob/master/Design/worlds.md).

## Story 

< TINY WORLDS > is set in an imaginary world, which should have similarities with a fantasy setting.
< NAME >, the main character, is a human with an unatural ability to explore people's thoughts. 
Throughout the game, < NAME > explores the worlds of many different types of people, and as a result
goes through a series of personal growths. 

At the start of the game, the player starts out in the mind of a little child and sees the world in 
a naive and innocent perspective. All elements of this world are peaceful towards the character and 
there should be minimal to no fears and worries in the child. 

< NAME > travels through different worlds after discovering the 'cores' of each person. The cores are 
the	dominating memories and experiences of the person, the experiences that shape them to who they are 
(similar to cores of the movie 'Inside Out'). 

Eventually, < NAME > travels to her own world without herself knowing. The world is quite barren, 
signalling the loneliness of her real life. The emptiness of the world is chilling, there is no sign 
of any other life. The only point of interest in the whole world is a core sitting in the middle of the
world. 

Once the main character discovers her core, it is revealed that she was orphaned and always left out 
in life. Having lived alone all her life, she was about to suicide in real life. The last scene should
show her sitting in a room with a rope ready to take her own life. 

After the depressing scenes, the screen will go dark. However, the friends she had made along her 
journey will show up in the last screen. Although imaginary, the friends color her life with lively
colors and in the end, it is shown that her world has become quite cheerful and full of life.

## Character(s)

< NAME > is the main character of the game. She has the ability to live in the thoughts of other
people, exploring the world they build for themselves in their minds. Her personality is quite mysterious
and unknown to the player in order to make interactions more personalized to the player instead of 
having the players play in the eyes of someone else. 

Attributes :
  - Short Blue Hair
  - Blue Eyes
  - Calm / Neutral Expressions

## Levels

Each world has a starting area that should reflect the outermost traits of the person, like physicality
and looks, etc. Upon moving deeper into the world, the surroundings will change to deeper characteristics,
like personality and fears, etc. 

Levels should have a clear flow to the path that the player should follow, and interactable objects should
stand out to the player. Even with a clear path to follow, it should also be open enough so that the 
player gets a sense of exploration while playing. 

Finally, there will be a 'core' at the end of each level, preferably after a boss fight or a significant
event of some sort. The core takes the form of an orb or a crystal, depending on the world it is in. The
color of the orb will represent the mood/idea of the core itself.

## Gameplay

After launching the game, an opening cutscene plays and transitions into the menu screen. The player has
two options, start game and settings (continue game if saving is implemented). Start game brings the 
player into the gameplay while settings lets the player change some game configurations.

The player can move in all 4 directions, but is more focused on horizontal movement rather than vertical 
movement (similar to castle crasher). The player will not be required to jump (but may be implemented if
time allows). 

One key value of the game is simplicity, and as such the player will need a maximum of two keys (not 
including movement keys) to play the whole game, since the player will use the mouse to interact with
game objects anyways. 

## Art

The style is simplistic but very dynamic. The style should feel like that of journey but in 2D, and it
should partially resemble the style of Ori and the Blind Forest. 

Animations will be saved in spritesheets, and sprites should be small and simplistic. The art should 
consist of simple and clean lines that have dynamic expressions. 

## Sound/Music 

The game will feature an 8-bit or music box sound track that contains multiple tracks. A track should play 
upon entering the game and over the menu. Each world will get a unique tune that fits with the theme
of the world. 

Sound effects will be added for almost every interaction in the game. This includes anything from player
interactions to footsteps to ambient noises (like bird chirps etc..).

## Development

I plan to spend 1 month finishing up the main game engine and the rest of the time on the content of 
< TINY WORLDS >. Everything will be created myself, from programming to art to sound.

< TINY WORLDS > will require a lot of art/assets for each different level. The character may require many
frames of animation depending on the amount of object interactions and the uniqueness of each interaction. 
Additionally, assets will need to be created for fonts, menus, particle FX as well as many different
types of creatures. If implemented, art will also be required for cutscenes and splash art.

The focus of programming will start with the development of the engine with a game state system. After
basic functions are implemented, the level system will be implemented to allow for the easy creation
of new and different levels. The programming should be done 1 month before the deadline to allow
for asset creation as well as debugging.

Music is the least significant part of the game, and as such will be started later on into the development
process, and same with Sound Effects.

![Development Cycle](https://github.com/ianw3214/TinyWorlds/blob/master/Design/DevCycle.png)

~~~

## Notes
  - replace < TINY WORLDS > with Game Title
  - replace < NAME > with main character name