

## Hardware Assembly Basics

1. Aquire parts similar or equal to that on the 'Parts List' spread sheet

2. From the '3D Print Models' Folder print out:
	a) 2 Spools
        b) 1 Pen holder
	c) 4 Eyehook mounts
        c) 1 Electronics enclosure (optional)

3. Fix the stepper motor brackets and electronics enclosure onto a piece of wood or any other suitable base plate.

4. Fix the stepper dampers (with two screws only per motor) to the motor brackets.

5. Fix the stepper motors to the stepper dampers (with two screws only per motor).

6. Connect the stepper motor driver to the micro-controller by referencing the pin definitions in the LSGMM.ino file.

7. Complete other electrical connections by referencing the motor driver and micro-controller datasheets.

8. Mount the 4 eyehook mounts to a wall surface with a double sided adhesive and screw in eyehooks.

9. Fix hubs to spools and mount onto motor shaft with hub set screw.

10. Route two lengths of fishing line, one per spool, on left and right side eye hooks.  

11. Tie string on each spool, and dab with super glue.

12. Thread string through pen holder holes and re-tie on each side.  Rubber washers can fix this string length such that the pen is balanced and perpendicular to the wall surface.

13. Center the pen to a desired location and measure the string lengths.  Input these initial conditions into the LSGMM.ino file and run the cal_menu() function in the void setup().

![Alt text](Helpful_Images/Base_Plate.png?raw=true "Title")


