# LSGMM (Large-Scale Generative Mark Maker)

This machine provides the foundation for a human-robot interaction study that examines viewer interest with respect to process-centric and audience-modifiable abstract drawings.  A minimalistic design approach was used to highlight the aesthetic effect of the drawing and the machine’s motion as opposed to its visual presence.  Viewer interaction will manifest in slight, yet immediate and identifiable marks that stitch together a piece over the course of days or even weeks.  Witnessing the arc of a macroscopic structure appear, and the microscopic contributions from past viewers, is fundamental to the research, and the installation as a whole.

Drawing machines, and hanging pen plotters in particular, have been widely implemented by both the art and maker communities.  Harvey Moon’s work integrated satellite images to stitch together map-based abstractions in a similar exhibit.  Mechanically, we look to expand on existing designs by detailing a more scalable infrastructure.  In terms of interaction, we aim to hone the balance between viewer agency and structure.  Inspiration has been taken both from founders of the generative art movement (Manfred Mohr, Frieder Nake) and traditional contemporary abstractionist (Agnes Martin, Ellsworth Kelly, Eva Hesse, Sol Lewitt).  Subsequent works will examine both the mechanical and algorithmic sources of randomness and imperfection to repeated marks.

The current design serves as a baseline for the project goals described above.  It is our hope that others with overlapping goals can utilize or build on the open source software and hardware.


## Getting Started

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


### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc

