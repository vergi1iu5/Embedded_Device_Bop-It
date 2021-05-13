# Embedded_Device_Bop-it

NOTE: Please read the PDF documentation.pdf in the docs

# Introduction

The basic idea for the project is quite simple: a less complex version of the game Pop-It.
The game presents the user with basic arithmetic problems based on the set difficulty. Every 4
rounds, the user must either: clap, press one of the joystick buttons, or shake the device. Doing
any of the previously mentioned actions counts as a wrong answer. User is rewarded with a 10
second time increase (game time set by user at start of game) and a pleasant sound when
answered correctly. If the user answers incorrectly, an unpleasant sound plays. Numerical
answers and problems are provided and displayed through the computer terminal. A beeping
sound indicates when time is about to runout by increasing in both frequency and duration.

The most interesting part for this project is the methodology used to develop the game.
Starting from the bottom down, specific hardware handlers are used to take input from Joystick,
terminal (UART), and onboard gyroscope, and sound recorded. For output, there are handlers to
display characters on the LCD screen, terminal, and play sounds. The handlers are essentially
just wrapper functions/files which utilize either the BSP drivers or HAL drivers provided by
STM but abstract most of the setup complexity or simplify the input to the drivers. On top of
these are the specific game mode threads (one for each targeted input, so either shake, clap, press
joystick, or input math problem answer). These threads communicate through a single message
queue to determine which input was provided by user first. An additional thread is used to
handle sounds to be played during the game. Lastly, a thread is used to coordinate all threads,
starting them all when an input is required, and stopping all when an input was received.
