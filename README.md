# IoT Buoy

<img src="https://mediad.publicbroadcasting.net/p/wxxi/files/styles/x_large/public/201907/bw9pc-0719_k.png" width="1000">

Lake Erie Algae Bloom 2019, (Image credit NOAA)

An open source, low-cost envirnmental buoy designed to monitor the health of lakes, rivers, estuaries and tidal regions with particular emphasis on algae blooms.
Designed by [Analytical Mechanics Associates](https://www.ama-inc.com/) and the [Virginia Modeling, Analysis & Simulation Center (VMASC)](https://www.odu.edu/vmasc). This project is compatible with the [Open Data Cube](https://www.opendatacube.org/), which is an open-source platform that can ingest data from a variety of sensors and has the goal of making environmental monitoring simple and highly accessible. An overview of the current progress is posted [here](https://github.com/oyetkin/iotbuoy/blob/main/BuoyPresentation1.pdf)

# Building your Buoy - Buoy Specific Hardware Required

### 1. [Arduino MEGA or ELEGOO MEGA](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Arduino-Compliant/dp/B01H4ZDYCE/ref=asc_df_B01H4ZDYCE/?tag=hyprod-20&linkCode=df0&hvadid=309751315916&hvpos=&hvnetw=g&hvrand=11900577637582741809&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9008124&hvtargid=pla-493625544636&psc=1&tag=&ref=&adgrpid=67183599252&hvpone=&hvptwo=&hvadid=309751315916&hvpos=&hvnetw=g&hvrand=11900577637582741809&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9008124&hvtargid=pla-493625544636)

- [Arduino MEGA R3](https://store.arduino.cc/usa/mega-2560-r3)

- [ELEGOO MEGA R3 (cheaper)](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Arduino-Compliant/dp/B01H4ZDYCE/ref=asc_df_B01H4ZDYCE/?tag=hyprod-20&linkCode=df0&hvadid=309751315916&hvpos=&hvnetw=g&hvrand=11900577637582741809&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9008124&hvtargid=pla-493625544636&psc=1&tag=&ref=&adgrpid=67183599252&hvpone=&hvptwo=&hvadid=309751315916&hvpos=&hvnetw=g&hvrand=11900577637582741809&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9008124&hvtargid=pla-493625544636)

### 2. [Adafruit Boost Converter](https://www.amazon.com/Module-Output-Voltage-Converter-Regulator/dp/B08NCM9ZPQ/ref=pd_lpo_2?pd_rd_i=B08NCM9ZPQ&th=1)

### 3. [SIM 808 GPRS/GSM Shield](https://www.robotshop.com/en/sim808-gps-gprsgsm-arduino-shield-mkf.html)

### 4. [Adafruit Solar Charger](https://www.adafruit.com/product/390?gclid=Cj0KCQiAkZKNBhDiARIsAPsk0Wjwwub03ZPgBxlKg1lHWn5nn0opyzVy_Q3VPSugYz3q11KsZ251EOcaAhBzEALw_wcB)

### 5. [Adafruit Data Logging Shield](https://www.adafruit.com/product/1141?gclid=EAIaIQobChMI9OqQ1tr58QIVzXxvBB3GTgbGEAQYASABEgITQvD_BwE)

- Requires [CR1220 Coin Cell Battery](https://www.grainger.com/product/54ZU79?ef_id=CjwKCAjwmeiIBhA6EiwA-uaeFeCfQyJyafe8bUuabPpTv9V-Dkiohqq99VO3asoSj661ExP630XgBhoCccUQAvD_BwE:G:s&s_kwcid=AL!2966!3!496359975085!!!g!484329633033!&gucid=N:N:PS:Paid:GGL:CSM-2293:99F1R6:20501231&gclid=CjwKCAjwmeiIBhA6EiwA-uaeFeCfQyJyafe8bUuabPpTv9V-Dkiohqq99VO3asoSj661ExP630XgBhoCccUQAvD_BwE&gclsrc=aw.ds)

- [Adafruit Data Logging Shield Board and Schematic](https://github.com/adafruit/Data-Logger-shield)

- [Adafruit Data Logging Shield Fritzing Object](https://github.com/adafruit/Fritzing-Library/blob/master/parts/Adafruit%20Datalogger%20Shield%20v1.fzpz)

### 6. [Adafruit ADS1115 Analog to Digital Converter](https://www.adafruit.com/product/1085?gclid=Cj0KCQjw0emHBhC1ARIsAL1QGNfJ3SJ85uZqejbk4At3gi_rBteSZwTxbq5_mKbJvcHG9wJhS_kqJ54aAu4vEALw_wcB)

- [ADS1115 Hardware Drivers](https://github.com/adafruit/Adafruit_ADS1X15)

- [ADS1115 Board and Schematics](https://github.com/adafruit/ADS1X15-Breakout-Board-PCBs)

- [ADS1115 Fritzing Object](https://github.com/adafruit/Fritzing-Library/blob/master/parts/Adafruit%20ADS1115%2016Bit%20I2C%20ADC.fzpz)

- [ADS1115 Data Sheet](https://cdn-shop.adafruit.com/datasheets/ads1115.pdf)

- [ADS1115 Sample Code](https://learn.adafruit.com/adafruit-4-channel-adc-breakouts/arduino-code)

### 7. [Adafruit 6V 3.5W Solar Panel](https://www.adafruit.com/product/500)

- [Solar Panel Technical Drawing](https://github.com/VoltaicEngineering/Solar-Panel-Drawings/blob/master/Voltaic%20Systems%203.5W%206V%20113x210mm%20DRAWING%20CURRENT%202017%207%2020.pdf)

### 10. [6600 mAh 3.7V Lithium Ion Battery](https://www.adafruit.com/product/353)

### 11. [Adafruit TPL5110 Breakout Board](https://www.adafruit.com/product/3435)

### 12. [Adafruit Power Boost 1000 Breakout Board](https://www.adafruit.com/product/2465?gclid=CjwKCAiA24SPBhB0EiwAjBgkhrGJI_mgLnF6EL7C2EgxJwRfddbmznOh6DxHYULQIVquQbLt4znxhRoCKecQAvD_BwE)

### 12. Housing
- Buoy with CAD files provided [here](https://github.com/oyetkin/iotbuoy/tree/main/CAD_Files)

- Waterproof box

- Your own design

# Fluorometer Design

### 1. [1 x 395 nm LED](https://www.mouser.com/ProductDetail/BIVAR/UV5TZ-390-15?qs=sGAEpiMZZMtaWn5d0uiAD8cVjFdgDZGx%2FUxBqCDWrPM%3D)

### 2. [FDS 100 Photodiode](https://www.thorlabs.us/thorproduct.cfm?partnumber=FDS100)

### 3. [550 nm Cut On Long Pass Filter](https://www.newport.com/p/10CGA-550)

### 4. [Jewler's Resin](https://www.amazon.com/16OZ-Epoxy-Resin-Graduated-Instructions/dp/B0839GN3PF/ref=sr_1_5?keywords=clear%2Bepoxy%2Bresin&qid=1638217693&qsid=146-2373950-0512811&s=arts-crafts&sr=1-5&sres=B08233BV5W%2CB08HN2XCDS%2CB0839GN3PF%2CB098918WFB%2CB084PZG6HK%2CB07S1MLQMJ%2CB084Q87Y8M%2CB07YCVVYFK%2CB099XFL1PK%2CB086L1CDMT%2CB07G5HY79C%2CB07JBKDQZJ%2CB07JB5P76Z%2CB089XZJFG5%2CB097JLGFZF%2CB07QF2XYYX%2CB092HX7SQT%2CB08PF576QC%2CB0823LC5H1%2CB08XQ2S1VQ&th=1)

### 5. [Black ABS Filament (will be useful for turbidity sensor as well)](https://www.amazon.com/HATCHBOX-3D-Filament-Dimensional-Accuracy/dp/B00J0H8EWA/ref=sr_1_3?crid=HBAP4Q1YHOWB&keywords=black%2Babs%2Bfilament%2B1.75%2B1kg&qid=1638217775&qsid=146-2373950-0512811&sprefix=black%2Babs%2Bfila%2Carts-crafts%2C167&sr=8-3&sres=B00J0H8EWA%2CB07XF5KM74%2CB07T2QZSLY%2CB01M6Y2QF1%2CB00MV7T25E%2CB07199449V%2CB00WX4UONO%2CB0919Q91MN%2CB015VGJGPW%2CB00F9MNMAY%2CB018F586ES%2CB08N4MMK6V%2CB089NPTH2W%2CB09H7RKL95%2CB07GFXYVLR%2CB08BR7YCY1&srpt=THERMOPLASTIC_FILAMENT&th=1)

# Turbidity Sensor Design

### 1. [2 x Photoresistors](https://www.amazon.com/gp/product/B01N7V536K/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&psc=1)

### 2. [1 x RGB LED](https://www.amazon.com/gp/product/B077XGF3YR/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)

### 3. [Jewler's Resin](https://www.amazon.com/16OZ-Epoxy-Resin-Graduated-Instructions/dp/B0839GN3PF/ref=sr_1_5?keywords=clear%2Bepoxy%2Bresin&qid=1638217693&qsid=146-2373950-0512811&s=arts-crafts&sr=1-5&sres=B08233BV5W%2CB08HN2XCDS%2CB0839GN3PF%2CB098918WFB%2CB084PZG6HK%2CB07S1MLQMJ%2CB084Q87Y8M%2CB07YCVVYFK%2CB099XFL1PK%2CB086L1CDMT%2CB07G5HY79C%2CB07JBKDQZJ%2CB07JB5P76Z%2CB089XZJFG5%2CB097JLGFZF%2CB07QF2XYYX%2CB092HX7SQT%2CB08PF576QC%2CB0823LC5H1%2CB08XQ2S1VQ&th=1)


### 4. [Black ABS Filament (will be useful for fluorometer as well)](https://www.amazon.com/HATCHBOX-3D-Filament-Dimensional-Accuracy/dp/B00J0H8EWA/ref=sr_1_3?crid=HBAP4Q1YHOWB&keywords=black%2Babs%2Bfilament%2B1.75%2B1kg&qid=1638217775&qsid=146-2373950-0512811&sprefix=black%2Babs%2Bfila%2Carts-crafts%2C167&sr=8-3&sres=B00J0H8EWA%2CB07XF5KM74%2CB07T2QZSLY%2CB01M6Y2QF1%2CB00MV7T25E%2CB07199449V%2CB00WX4UONO%2CB0919Q91MN%2CB015VGJGPW%2CB00F9MNMAY%2CB018F586ES%2CB08N4MMK6V%2CB089NPTH2W%2CB09H7RKL95%2CB07GFXYVLR%2CB08BR7YCY1&srpt=THERMOPLASTIC_FILAMENT&th=1)

# Other Items Required

- SD Card
- Jumper wires
- Header pins
- Solder
- Soldering iron
- Wire strippers
- Heat shrink tubing
- Electrical tape
- DP 100 epoxy
- Rope/anchor OR Rope/mooring OR free-floating

# Other Interesting Sensors

- [BME 680 Temperature, Pressure and Humidity Sensor](https://www.adafruit.com/product/3660)

- [DHT-11 Temperature/Humidity Sensor](https://www.adafruit.com/product/386)

- [DHT-22 Temperature/Humidity Sensor](https://www.adafruit.com/product/385)

- [Waterproof Thermistor](https://www.adafruit.com/product/372)

- [pH Sensor - TEKCOPLUS](https://www.amazon.com/Replacement-Electrode-Connector-Controller-Hydroponics/dp/B09681C36B/ref=sr_1_19?dchild=1&keywords=ph+meter+electrode&qid=1629149917&sr=8-19)
OR
- [pH Sensor - Vernier](https://www.vernier.com/product/ph-sensor/)

- [Turbidity Sensor](https://www.digikey.com/en/products/detail/amphenol-advanced-sensors/TSD-10/4767843?utm_adgroup=Sensors%20%26%20Transducers&utm_source=google&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_RLSA_Buyers&utm_term=&utm_content=Sensors%20%26%20Transducers&gclid=CjwKCAjwmeiIBhA6EiwA-uaeFRJvJ3rLHPiHJND-PSO5aePXsmi2i962wfCCjfp96LtXLJMJ6MAUsBoClz0QAvD_BwE)

- [MPU 6050 Inertial Measurement Unit (for wave height, direction etc.)](https://www.adafruit.com/product/3886)

# Fabrication

- Read the "Complete Guide to Building Your Very Own Algae Monitoring Buoy"

# Viewing Results

- Download jupyter to your computer and run "Visualization_Notebook.ipynb"
