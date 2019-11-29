# LSGMM (Large-Scale Generative Mark Maker)

This machine provides the foundation for a human-robot interaction study that examines viewer interest with respect to process-centric and audience-modifiable abstract drawings.  A minimalistic design approach was used to highlight the aesthetic effect of the drawing and the machine’s motion as opposed to its visual presence.  Viewer interaction will manifest in slight, yet immediate and identifiable marks that stitch together a piece over the course of days or even weeks.  Witnessing the arc of a macroscopic structure appear, and the microscopic contributions from past viewers, is fundamental to the research, and the installation as a whole.

Drawing machines, and hanging pen plotters in particular, have been widely implemented by both the art and maker communities.  Harvey Moon’s work integrated satellite images to stitch together map-based abstractions in a similar exhibit.  Mechanically, we look to expand on existing designs by detailing a more scalable infrastructure.  In terms of interaction, we aim to hone the balance between viewer agency and structure.  Inspiration has been taken both from founders of the generative art movement (Manfred Mohr, Frieder Nake) and traditional contemporary abstractionist (Agnes Martin, Ellsworth Kelly, Eva Hesse, Sol Lewitt).  Subsequent works will examine both the mechanical and algorithmic sources of randomness and imperfection to repeated marks.

The current design serves as a baseline for the project goals described above.  It is our hope that others with overlapping goals can utilize or build on the open source software and hardware.

![Alt text](Large_Scale_Plotter.jpg?raw=true "Title")

## File Guide

**Code Base**:
- Code base used to program Teensy 3.5 micro-controller via the Arduino IDE.  The setup and loop functions are located within the main file LSGMM.ino.  The code for the 'Bezier Node' drawing can be found in the node_bezier_alg.ino file.  The code for the 'Worn Structure' drawing can be found in the worn_structue.ino file.
- Libraries used within the LSGMM code base.  Add these to the Library Arduino folder before compilation.

**Hardware Assembly**:
- 3D print models
- Basic assembly instructions
- Bill of Materials 

**Media**:
- Exhibition Drawings
- Introductory project video

## Reference

A. Phillips, N. Fitter, and A Vinoo, "May I Draw Your Attention?  Initial Lessons from the Large-Scale Generative Mark Maker", The IEEE International Conference on Robotics and Automation [Pending], 2019.

* **Aidan Phillips** - aidan.instance@gmail.com []()
* **Naomi T. Fitter** - naomi.fitter@oregonstate.edu[]()
* **Ashwin Vinoo** - vinooa@oregonstate.edu[]()


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details



