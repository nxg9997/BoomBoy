# BoomGirl (BoomBoy Level Editor)

## About

BoomGirl is an Electron-based level editor for BoomBoy.

## To Use

To run BoomGirl, launch a terminal window from within this folder and run the following commands:

```bash
# Install dependencies
npm install
# Run the app
npm start
```

## Instructions

### Controls Bar

Dropdown - Swap between placing rectangular platforms and the player object.

Polygon Generator - (1st Box) Directly input the vertices for the polygon in a JSON format. (2nd Box) Input a new vertex position. (Add Vertex) Click to append the vertex from (2nd Box) to the polygon. (Remove Vertex) Click to discard the newest vertex from the polygon vertex list. (Add Polygon) Click to generate a polygon based on the vertices inside the (1st Box).

Output File - Click to create a level data file within the BoomBoy source files.

Change Level Size - (Box) Directly input the width and height of the level in a JSON format. (Change Size) Click to change the level size to match the data from (Box).

Play - Click to play BoomBoy.

### Console Log

The bottom-left contains a textbox that will display messages about the status of the editor.

### Editing Geometry

Right-click to place a rectangular platform at the mouse position. Rectangular blocks can be stretched and moved around the level by left-clicking and useing the on-screen controls.

Place a custom polygon by using the Polygon Generator in the Controls Bar. Polygons can be moved, but their size cannot (or should not) be modified due to not being supported by BoomBoy.

### Other

BoomGirl will automatically open the level data file from the BoomBoy source files when launching.