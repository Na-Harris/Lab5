# TOOP Lab 5
This lab exercise is closed book/closed notes except for these websites:
* [cplusplus.com website](https://cplusplus.com/)
* [Pololu 3 pi plus 32U4 arduino library](https://github.com/pololu/pololu-3pi-plus-32u4-arduino-library)
* [Platform IO Pololu3piplus32U4 Installation Guide](https://registry.platformio.org/libraries/pololu/Pololu3piPlus32U4/installation)
* [TOOP Robot Setup Guide](https://github.com/CGA-TOOP/PlatformIOSetup)
* And any code previous developed and saved in your local VSCode directories
  
This Lab is individual effort. It is to be completed in person on the Platform IO IDE. This lab is worth 50 points and you will have 75 minutes to complete it. You must synchronize your main.cpp file in github classroom directory in order to sumbit the Lab 5 exercise.  This means you will need to copy/paste your main.cpp from your PlatformIO project into your github classrooms directory, then synchronize.  **Check with your instructor prior to departing to ensure your Lab is properly submitted**

# Lab Procedures
You must write a program that informs the user if a button is being held at any given time
1. In `setup()`
  - Initialize the OLED, turnsensor,
  - Display your name on the top line of the OLED (it should remain there for the duration of your program).  Ensure your entire name fits on the first line. 
2. Write a user defined function called `lab5()` that does the following:
  - If button A is pressed, turn clockwise 90 degrees.  Print “Turning Right” on the second line of the OLED.
  - If button B is pressed, turn counterclockwise 90 degrees. Print “Turning Left” to the second line of the OLED. 
  - If button C is pressed, travel forward until the robot senses a black line. Print “Moving Forward” to the second line of the OLED.
  - If none of the above buttons are pressed display “Waiting…” to the second line of the OLED.
[!Note]
You must remove any unnecessary characters from the OLED; hint: add blank spaces for each OLED string to “erase” any previous text. 
3. In `loop()`
  - Call your function from section 2. 
  - Pause for 1/2 a second.

