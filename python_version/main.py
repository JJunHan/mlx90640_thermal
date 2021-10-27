import numpy as np
# import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
# import json
# import os
# import sys
import time
import board
import busio
import adafruit_mlx90640
# from sklearn.cluster import DBSCAN
from pylab import *
from scipy.ndimage import measurements


#print('Python version: ', sys.version_info)

# I2C interface 
i2c = busio.I2C(board.SCL, board.SDA, frequency=400000)
mlx = adafruit_mlx90640.MLX90640(i2c)
print("MLX addr detected on I2C", [hex(i) for i in mlx.serial_number])
mlx.refresh_rate = adafruit_mlx90640.RefreshRate.REFRESH_8_HZ

# Visualizing Tools
plt.ion()
fig, axs = plt.subplots(1, 1) #2,1

def main():
    frame = np.zeros((768)) #[0] * 768
    current_frame = np.zeros((24,32))
    while(1):

        try:
                mlx.getFrame(frame)
            #except ValueError:
        except:
            print("Potential I/O Error")
            continue

        for i in range(0,24):
            # 24 x 32  (Height x Width)
            current_frame[i,:] = frame[32*i : 32*(i+1)]


        # Show on plot
        visualize(current_frame)

def visualize(current_frame):
    sns.heatmap(current_frame[:,:] , cmap="vlag" , vmin=15 ,vmax=40, cbar=False, ax = axs)#, ax = axs[0,0])
    #axs.imshow(event[:,:] , cmap='Greys')
    #axs[1].imshow(test[:,:] , cmap='Greys')
    plt.pause(0.1)
    #plt.clf()
    #plt.show()

if __name__ == "__main__":
    # Begin main program
    main()

