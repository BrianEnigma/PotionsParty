# Potions Cabinets



## Parts

- Electronics Hardware
  - [Hall Effects Transistor](http://d.digikey.com/n0SB0gX00vpN0KX0fL0C752)
  - [Solenoid](https://www.adafruit.com/product/1512)
  - [Power Transistors](https://www.adafruit.com/product/976)
  - [Diode](https://www.adafruit.com/product/755)
  - [12VDC Power](https://www.adafruit.com/product/798)
  - [Arduino Pro Mini](https://www.adafruit.com/product/2378)
  - [Power Jack](https://www.adafruit.com/product/610)
  - assorted bits, bobs, wires, solder, protoboards, etc.
- Carpentry Hardware
  - [Hinges](https://smile.amazon.com/gp/product/B01FXIIKUU/ref=oh_aui_detailpage_o08_s00?ie=UTF8&psc=1)
  - [Corners](https://smile.amazon.com/gp/product/B0154647RG/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
  - [Door Springs](https://www.homedepot.com/p/Everbilt-Spring-Assortment-Kit-84-Pack-13554/203133714)



## Contents

- [80ml Test Tubes](https://smile.amazon.com/gp/product/B072ZQ4DS9/ref=oh_aui_detailpage_o06_s00?ie=UTF8&psc=1)
    - diameter: 25mm
    - length: 198mm
    - volume: 80ml (big enough for a 2oz pour)
- [Eye-dropper bottles (SKU:DPA10)](https://www.specialtybottle.com/glass-bottles/european-dropper/amber)
    - diameter: 39mm
    - height: 120mm



## Lessions Learned

- There's a tradeoff between spring and solenoid. A stronger spring means the door pops open further, but it also means more friction between the latch and the solenoid slug. I've mitigated this a bit by waxing the latch. Doing this again, I might want to use two solenoids: one as a latch and one to kick the door open. Though hopefully that kick wouldn't be too forceful and/or loud.
- The really awesome decorative corners have a flaw in the current design. They're metal and too close to the keyhole. The magnets get sucked toward the metal corner, away from the sensor. From the sensor/functional point of view. this is less of a problem for the big magnets, since they're strong enough to have a good range, but doesn't work well with the small magnets. Tech aside — the overall experience feels a bit tarnished. You suddenly _know_ you're using a magnet when it sticks to the corner. In the future, move the keyhole or remove the corners. Maybe move the keyhole to the center of the frame? 
- The breakout board off the Arduino Pro Mini could use multiple power+ground terminals. Trying to jam 4 ground wires into a mini terminal block is a pain.


