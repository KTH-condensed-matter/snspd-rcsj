#!/usr/bin/env python3
import h5py
import numpy as np
from matplotlib import pyplot as plt

with h5py.File('out_2020-09-23-120500.h5', 'r') as data:
    voltage = np.array(data['voltage'][:])

plt.plot(range(len(voltage)), voltage)
plt.xlabel('Time')
plt.ylabel('Voltage')
plt.show()


