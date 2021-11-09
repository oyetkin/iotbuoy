import urllib.request, json
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import yagmail
from matplotlib.widgets import Slider, Button
import matplotlib as mpl
import numpy as np
import datetime as dt

legend = plt.legend()

def animate(i):
    with urllib.request.urlopen("http://52.26.55.255:8080/api/v0p1/sensor_by_id/Ursula_2") as url:
        data = json.loads(url.read().decode())
    df = pd.DataFrame.from_records(data)

    year = (dt.datetime.now() + dt.timedelta(days = 1)).year
    month = (dt.datetime.now() + dt.timedelta(days = 1)).month
    day = (dt.datetime.now() + dt.timedelta(days = 1)).day
    hour = (dt.datetime.now() + dt.timedelta(days = 1)).hour

    fluorescence = df[df['measurement_name'] == 'fluorescence']
    fluortimes = pd.to_datetime(fluorescence['timestamp']).tolist()
    fluorvals = fluorescence['value'].tolist()

    redturb1 = df[df['measurement_name'] == 'redturbidity']
    redturb1times = pd.to_datetime(redturb1['timestamp']).tolist()
    redturb1vals = redturb1['value'].tolist()

    redturb2 = df[df['measurement_name'] == 'redturbidity2']
    redturb2times = pd.to_datetime(redturb2['timestamp']).tolist()
    redturb2vals = redturb2['value'].tolist()

    greenturb1 = df[df['measurement_name'] == 'greenturbidity']
    greenturb1times = pd.to_datetime(greenturb1['timestamp']).tolist()
    greenturb1vals = greenturb1['value'].tolist()

    greenturb2 = df[df['measurement_name'] == 'greenturbidity2']
    greenturb2times = pd.to_datetime(greenturb2['timestamp']).tolist()
    greenturb2vals = greenturb2['value'].tolist()

    blueturb1 = df[df['measurement_name'] == 'blueturbidity']
    blueturb1times = pd.to_datetime(blueturb1['timestamp']).tolist()
    blueturb1vals = blueturb1['value'].tolist()

    blueturb2 = df[df['measurement_name'] == 'blueturbidity2']
    blueturb2times = pd.to_datetime(blueturb2['timestamp']).tolist()
    blueturb2vals = blueturb2['value'].tolist()

    temperature = df[df['measurement_name'] == 'temperature']
    temperaturetimes = pd.to_datetime(temperature['timestamp']).tolist()
    temperaturevals = temperature['value'].tolist()

    pH = df[df['measurement_name'] == 'pH']
    pHtimes = pd.to_datetime(pH['timestamp']).tolist()
    pHvals = pH['value'].tolist()

    plt.scatter(fluortimes, fluorvals, color='y', label="Fluorometer Voltage")
    plt.scatter(redturb1times, redturb1vals, color='r', label="Red Turb 1")
    plt.scatter(greenturb1times, greenturb1vals, color='g', label="Green Turb 1")
    plt.scatter(blueturb1times, blueturb1vals, color='b', label="Blue Turb 1")

    # plt.scatter(temperaturetimes, temperaturevals, color='k')
    # plt.scatter(pHtimes, pHvals, color='c')
    plt.legend(loc="upper right")

    plt.axis([dt.date(2021, 11, 7), dt.date(year, month, day), None, None])

    # plt.plot(redturb2times, redturb2vals, color=cmap(50))
    # plt.plot(greenturb2times, greenturb2vals, color=cmap(50))
    # plt.plot(blueturb2times, blueturb2vals, color=cmap(50))

    print("Fluorometer Val: " + str(fluorvals[-1]) + " Red Turb 1: " + str(redturb1vals[-1]) + " Green Turb 1: " + str(greenturb1vals[-1])
          + " Blue Turb 1: " + str(blueturb1vals[-1]) + " Red Turb 2: " + str(redturb2vals[-1]) + " Green Turb 2: " + str(greenturb2vals[-1])
          + " Blue Turb 2: " + str(blueturb2vals[-1]) + " Water Temp: " + str(temperaturevals[-1]) + " pH: " + str(pHvals[-1]))

fig = plt.figure()
ani = animation.FuncAnimation(fig, animate, interval=60000)
plt.show()