import urllib.request, json
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import yagmail
alert_already = 0
def animate(i):
    with urllib.request.urlopen("http://52.26.55.255:8080/api/v0p1/sensor_by_id/Ursula_2") as url:
        data = json.loads(url.read().decode())
    df = pd.DataFrame.from_records(data)

    fluorescence = df[df['measurement_name'] == 'fluorescence']
    fluortimes = fluorescence['receipt_time'].tolist()
    fluorvals = fluorescence['value'].tolist()

    redturb1 = df[df['measurement_name'] == 'redturbidity']
    redturb1times = redturb1['receipt_time'].tolist()
    redturb1vals = redturb1['value'].tolist()

    redturb2 = df[df['measurement_name'] == 'redturbidity2']
    redturb2times = redturb2['receipt_time'].tolist()
    redturb2vals = redturb2['value'].tolist()

    greenturb1 = df[df['measurement_name'] == 'greenturbidity']
    greenturb1times = greenturb1['receipt_time'].tolist()
    greenturb1vals = greenturb1['value'].tolist()

    greenturb2 = df[df['measurement_name'] == 'greenturbidity2']
    greenturb2times = greenturb2['receipt_time'].tolist()
    greenturb2vals = greenturb2['value'].tolist()

    blueturb1 = df[df['measurement_name'] == 'blueturbidity']
    blueturb1times = blueturb1['receipt_time'].tolist()
    blueturb1vals = blueturb1['value'].tolist()

    blueturb2 = df[df['measurement_name'] == 'blueturbidity2']
    blueturb2times = blueturb2['receipt_time'].tolist()
    blueturb2vals = blueturb2['value'].tolist()

    temperature = df[df['measurement_name'] == 'temperature']
    temperaturetimes = temperature['receipt_time'].tolist()
    temperaturevals = temperature['value'].tolist()

    pH = df[df['measurement_name'] == 'pH']
    pHtimes = pH['receipt_time'].tolist()
    pHvals = pH['value'].tolist()

    ax1.clear()
    ax1.plot(fluortimes, fluorvals, label = "Fluorometer Data")
    ax1.legend()

    ax2.clear()
    ax2.plot(redturb1times, redturb1vals, label = "Red Turb 1 Data")
    ax2.legend()

    ax3.clear()
    ax3.plot(redturb2times, redturb2vals, label = "Red Turb 2 Data")
    ax3.legend()

    ax4.clear()
    ax4.plot(greenturb1times, greenturb1vals, label = "Green Turb 1 Data")
    ax4.legend()

    ax5.clear()
    ax5.plot(greenturb2times, greenturb2vals, label = "Green Turb 2 Data")
    ax5.legend()

    ax6.clear()
    ax6.plot(blueturb1times, blueturb1vals, label = "Blue Turb 1 Data")
    ax6.legend()

    ax7.clear()
    ax7.plot(blueturb2times, blueturb2vals, label = "Blue Turb 2 Data")
    ax7.legend()

    # ax8.clear()
    # ax8.plot(blueturb2times, blueturb2vals, label = "Blue Turb 2 Data")
    # ax8.legend()

    # ax1.plot()
    # if fluorvals[-1] > 1.0: # and alert_already == 0:
    #     yag = yagmail.SMTP('ahorvath1994@gmail.com', 'password')
    #     contents = ['Fluorometer value was found to be',
    #                 fluorvals[-1]]
    #     yag.send('alexander.horvath@ama-inc.com', 'Fluorometer Alert', contents)
    #     # alert_already = 1

fig = plt.figure()
ax1 = fig.add_subplot(1,8,1)
ax2 = fig.add_subplot(1,8,2)
ax3 = fig.add_subplot(1,8,3)
ax4 = fig.add_subplot(1,8,4)
ax5 = fig.add_subplot(1,8,5)
ax6 = fig.add_subplot(1,8,6)
ax7 = fig.add_subplot(1,8,7)
ax8 = fig.add_subplot(1,8,8)

ani = animation.FuncAnimation(fig, animate, interval=10000)
plt.show()