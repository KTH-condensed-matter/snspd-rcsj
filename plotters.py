import h5py
import numpy as np
from matplotlib import pyplot as plt


def plot_vt(file):
    with h5py.File(file, 'r') as data:
        voltage = np.array(data['voltage'][:])
        time = np.array(data['time'][:])

    plt.plot(time, voltage)
    plt.xlabel('Time $t R / L_k$')
    plt.ylabel('Voltage $V / R I_c$')
    plt.show()


def plot_it(file):
    with h5py.File(file, 'r') as data:
        bias_current = np.array(data['bias_current'][:])
        time = np.array(data['time'][:])

    plt.plot(time, bias_current)
    plt.xlabel('Time $t R / L_k$')
    plt.ylabel('Bias current $I_b / I_c$')
    plt.show()


def plot_iv(file):
    with h5py.File(file, 'r') as data:
        voltage = np.array(data['voltage'][:])
        bias_current = np.array(data['bias_current'][:])

    plt.plot(bias_current, voltage)
    plt.xlabel('Bias current $I_b / I_c$')
    plt.ylabel('Voltage $V / R I_c$')
    plt.show()
