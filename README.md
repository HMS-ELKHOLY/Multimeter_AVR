
[embed]https://github.com/HMS-ELKHOLY/Multimeter_AVR/blob/master/avr.pdf[/embed]
### Fayoum University Faculty of Engineering Computer and Systems Department 3rd year

#### Course :Lab and Measurements **ECE310**






## **multimeter with AVR**

**Theory**

- to measure current shunt resistor connected to convert current to voltage

 - Current=VOLTAGE/100(shunt resistor)

- to measure higher than 5 volts we used that circuit

  - voltage is minimized by using op amp with selecting right gain (rf/rin)

   - gain =1 for signal between (0:5)V

   - gain =0.5 for signal between (5:10)V

   - gain =0.25 for signal between (0:20)V

  - selecting gain done with **cd4066 ic**

  - start looping around pins of VOLTAGE\_GAIN block from one that gives smallest to

largest gain





  - if measured voltage larger than the value that can be measured by next pin loop exits

to save ADC pin from damage

#### **Application**

- using ADC pin 0 voltage can be measured

- PB0,PB1 are conﬁgured to pull up

- if pin PB0 pulled to low (pressed switch current is measured

- if pin PB0 pulled to high (not pressed switch voltage is measured

- if pin PB1 pulled to low (pressed switch) DC is measured

- if pin PB1 pulled to high (not pressed switch )RMS is measured

#### **RMS:**

**ﬁrst method(failed)**

 - make timer 1 at CTC mode and sample at suitable frequency like 1000 HZ

calculate RMS=SUM(voltage^2/samples\_number)

**second method (succeed):**

- use software loop to calculate RMS without using timer (suspend the program for

a while)

**Demo :**





