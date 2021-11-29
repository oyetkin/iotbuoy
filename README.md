# IoT Buoy

<img src="https://mediad.publicbroadcasting.net/p/wxxi/files/styles/x_large/public/201907/bw9pc-0719_k.png" width="1000">

Lake Erie Algae Bloom 2019, (Image credit NOAA)

An open source, low-cost envirnmental buoy designed to monitor the health of lakes, rivers, estuaries and tidal regions with particular emphasis on algae blooms.
Designed by [Analytical Mechanics Associates](https://www.ama-inc.com/) and the [Virginia Modeling, Analysis & Simulation Center (VMASC)](https://www.odu.edu/vmasc). This project is compatible with the [Open Data Cube](https://www.opendatacube.org/), which is an open-source platform that can ingest data from a variety of sensors and has the goal of making environmental monitoring simple and highly accessible. 

# Hardware required

### 1. Arduino MEGA or ELEGOO MEGA

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

### 12. [2 x Logic Level MOSFETs](https://www.adafruit.com/product/355?gclid=Cj0KCQiAkZKNBhDiARIsAPsk0WjnNOXiQNRGiAEgli75LM5E2M7oeG2U099ojSzUixjhvhauOlB4FwMaAmLGEALw_wcB)

### 13. [1 x 5V Relay](https://www.amazon.com/dp/B00LW15A4W/ref=sspa_dk_detail_1?psc=1&pd_rd_i=B00LW15A4W&pd_rd_w=aOwYS&pf_rd_p=887084a2-5c34-4113-a4f8-b7947847c308&pd_rd_wg=d9OYw&pf_rd_r=2T88CXQQATMBQ5GCT5P3&pd_rd_r=3e0135cb-89a8-48af-9e94-0d640f9c0973&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFDTlpFWDJKQjc1U04mZW5jcnlwdGVkSWQ9QTA4Mjc2MTYzQVJSVUhUQzg2RFlLJmVuY3J5cHRlZEFkSWQ9QTAwNzIwMDAzMFYxS09RSEVZQ0ZVJndpZGdldE5hbWU9c3BfZGV0YWlsJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

### 14. Housing
- Buoy with CAD files provided

- Waterproof box

- Your own design


# Fluorometer Design

# Turbidity Sensor Design

### 15. Application Specific Sensors

- [BME 280 Temperature, Pressure and Humidity Sensor](https://www.adafruit.com/product/2652?gclid=CjwKCAjwmeiIBhA6EiwA-uaeFSZ-NF_fIGoMKItD13WAFwLuqSzOlsIt3QiFYIm7f4G2JHgIPPHd5BoCa6EQAvD_BwE)

- [DHT-11 Temperature/Humidity Sensor](https://www.adafruit.com/product/386)

- [DHT-22 Temperature/Humidity Sensor](https://www.adafruit.com/product/385)

- [Waterproof Thermistor](https://www.adafruit.com/product/372)

- [Dissolved Oxygen Sensor](https://www.vernier.com/product/go-direct-optical-dissolved-oxygen-probe/)
OR
- [Dissolved Oxygen Sensor](https://atlas-scientific.com/mini-d-o-probe/)

- [pH Sensor - BaiBiinoom](https://www.amazon.com/dp/B08T14MHYM/ref=sspa_dk_detail_5?psc=1&pd_rd_i=B08T14MHYM&pd_rd_w=985e5&pf_rd_p=887084a2-5c34-4113-a4f8-b7947847c308&pd_rd_wg=uMPfo&pf_rd_r=P2YGNQ6FN71QT09KWQ5C&pd_rd_r=686f8153-25fd-4026-99d0-7fb76ffa969c&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExOUZRSlJLT0NGOFg1JmVuY3J5cHRlZElkPUEwMDczNzQyMktISUpDUU1BMDlINyZlbmNyeXB0ZWRBZElkPUEwOTQ1MDQxM0dNN0RCVURDSUsxNiZ3aWRnZXROYW1lPXNwX2RldGFpbCZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)
OR
- [pH Sensor - TEKCOPLUS](https://www.amazon.com/Replacement-Electrode-Connector-Controller-Hydroponics/dp/B09681C36B/ref=sr_1_19?dchild=1&keywords=ph+meter+electrode&qid=1629149917&sr=8-19)
OR
- [pH Sensor - Vernier](https://www.vernier.com/product/ph-sensor/)

- [Low Cost 3D Printed Optical Density Sensor (CAD Files to be added)]

- [Conductivity Sensor](https://www.vernier.com/product/go-direct-conductivity-probe/)

- [Turbidity Sensor](https://www.digikey.com/en/products/detail/amphenol-advanced-sensors/TSD-10/4767843?utm_adgroup=Sensors%20%26%20Transducers&utm_source=google&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_RLSA_Buyers&utm_term=&utm_content=Sensors%20%26%20Transducers&gclid=CjwKCAjwmeiIBhA6EiwA-uaeFRJvJ3rLHPiHJND-PSO5aePXsmi2i962wfCCjfp96LtXLJMJ6MAUsBoClz0QAvD_BwE)

- [MPU 6050 Inertial Measurement Unit (for wave height, direction etc.)](https://www.adafruit.com/product/3886)

- [Vernier Sensors](https://www.vernier.com/product-category/?category=sensors&page_num=1)

### 16. Miscellaneous

- Zip Ties
- SLA Resin
- SD Card
- Jumper wires
- Header pins
- Solder
- Soldering iron
- Wire strippers
- Heat shrink tubing
- DP 100 epoxy
- 1/8 inch thick plexiglass cover
- [Wide Angle Amber LEDs](https://lighthouseleds.com/3mm-diffused-flat-top-led-amber-orange-ultra-bright.html?gclid=CjwKCAjwmeiIBhA6EiwA-uaeFbw4fVEH2iwfen9D4Wmm7OOYcc3WVievBPmKvrvILAAn2A_0q_WB3RoCfAoQAvD_BwE)
- Rope/anchor OR Rope/mooring OR free-floating

- [I2C Overview](https://learn.adafruit.com/i2c-addresses)

- [Non-Exhaustive List of I2C Sensors and Addresses](https://learn.adafruit.com/i2c-addresses/the-list)

### Harmful Algae Bloom Information

- [HAB Guides and more](https://wcwc.ca/cyanobacteria-cyanotoxins/)
