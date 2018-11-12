## introduction
I don't know how do you drink your tea, but for me it goes like the following:

+ Boil water
+ Throw in the filter
+ taste it
+ It's too hot and It burns my tounge
+ Let it cool for a while
+ Forget about it
+ It gets too cold
+ Reheat it
+ Repeat

And this circle continues until the day has ended, or I get impatient and drink it cold.
To end this nightmare I created the **Tea Thermometer**.  It's a little piece of circuit,
that plays your favorite tune (which is currently Darude - Sandstorm), when the tea reached the *optimal* drinking temperature.

## Use cases
Although the title says Tea thermometer, It can be used in different situations as well, such as:

+ A too hot soup that needs cooling
+ A body thermometer which alerts you when you no longer have fever, so you can continue being awesome

The possibilities are endless!

## device
The Hardware design is maintained in the TeaThermometerHW repository.
To summarize, it has:
+ 2 LED 7 segment displays, to display the current temperature
+ 2 pushbuttons to interface it
+ A CR2032 Coin cell battery, which is supposed to be enough for years of operation!
(Well I can't confirm that one yet)
+ An STM32l011K4 microcontroller. This is the main device which runs the firmware written in this repository
+ A buzzer to produce those sweet tunes


## Features
+ The *optimal* temperature is different for everyone, so by long pressing one of the buttons it enters a temperature setting state, where you can set your own *optimal* temperature.
+ The software detects when the device was inserted to the tea, and acts accordingly
+ If the device has been turned on, but haven't been put in a hot drink for a while, then it turns itself off to save power.

## Future Features
+ Battery checking: The device warns the user when the battery needs to be replaced, by checking the battery voltage
+ Multiple selectable alert tunes. I'm already getting tired of the current available song..

## Build instructions
The project uses the [Embedded Template Library](https://github.com/ETLCPP/etl) as a submodule, so the project should be cloned with the submodules as well:
```bar
git clone --recurse-submodules -j8 https://github.com/EdBuilds/TeaThermometer.git
cd TeaThermometer
```

### Prerequisites
To start building the project, currently you will need the latest Eclipse, with system workbench installed, which can be found [here](http://www.openstm32.org/HomePage)

### Importing the project
You can import the cloned project to your eclipse workspace, by clicking on the *File -> Import projects from file system*. Clicking on the *Directory...* button you can select the cloned repository. Here it should automatically detect an eclipse project, so you can click on *Finish*

More detailed build instructions are coming later!
