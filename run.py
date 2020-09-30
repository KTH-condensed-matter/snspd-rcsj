#!/usr/bin/env python3
import argparse
import json
import logging
import os
from pathlib import Path

import h5py
from PyInquirer import prompt

import plotters


class PlotterCli:

    def __init__(self):

        # Parse arguments
        parser = argparse.ArgumentParser(description='Plot data from simulations')
        parser.add_argument('-v', '--verbose', action='count', default=0, help='set verbose level '
                                                                               '(-v = INFO, -vv = DEBUG)')
        parser.add_argument('-l', '--logs', type=str, default='plot.log', help='set where logs should be stored')
        parser.add_argument('-i', '--input', type=str, default='data', help='directory to load data files from')

        self.args = parser.parse_args()

        # Enable logging
        self.logger = logging.getLogger('plotter-cli')
        self.logger.setLevel(logging.DEBUG if self.args.verbose >= 2 else (logging.INFO if self.args.verbose == 1
                                                                           else logging.WARN))
        file_stream = logging.FileHandler(self.args.logs)
        file_stream.setFormatter(logging.Formatter('%(asctime)-15s %(levelname)-8s %(message)s'))
        self.logger.addHandler(file_stream)

    def run(self):

        plot_mode = None

        # Select plot type and file
        while True:

            if plot_mode is None:
                plot_mode = self._select_plot_mode_()

            file = self._select_file_()

            if file == 'change_plot_type':
                plot_mode = None
                continue

            # Call plotter with name plot_${plot_mode}
            getattr(plotters, 'plot_{}'.format(plot_mode))(file)

    def _select_plot_mode_(self):
        question = {
            'type': 'list',
            'name': 'mode',
            'message': 'Select the plotting mode',
            'choices': [{
                'name': 'Voltage vs Time',
                'value': 'vt'
            }, {
                'name': 'Bias current vs Time',
                'value': 'it'
            }, {
                'name': 'Voltage vs Bias current',
                'value': 'iv'
            }]
        }

        result = prompt(question)

        try:
            return result['mode']
        except Exception as e:
            self.logger.error(e)
            exit(0)

    def _select_file_(self):

        files = [{
            'name': self._format_file_config_(self._parse_file_config_(file)),
            'value': file
        } for file in self._get_files_()]

        files.append({
            'name': 'Change plot type',
            'value': 'change_plot_type'
        })

        question = {
            'type': 'list',
            'name': 'file',
            'message': 'Select a file',
            'choices': files
        }

        result = prompt(question)

        try:
            return result['file']
        except Exception as e:
            self.logger.error(e)
            exit(0)

    def _get_files_(self):
        path = Path(self.args.input)

        files = sorted([os.path.join(str(path), o) for o in os.listdir(str(path))
                 if not os.path.isdir(os.path.join(str(path), o)) and o.endswith('.h5')])

        return files

    @staticmethod
    def _parse_file_config_(file):
        with h5py.File(file, 'r') as data:
            json_config = data['json_config'][()]

        return json.loads(json_config)

    @staticmethod
    def _format_file_config_(config):
        initial = config['initial']
        return 'sz={sz}, st={st}, av={av}, dt={dt}, q={q}, c0={c0}, vg={vg}, nl={nl}, ib={ib}'.format(
            sz=initial['size'],
            st=initial['maxSteps'],
            av=initial['average'],
            dt=initial['dt'],
            q=initial['q'],
            c0=initial['c0'],
            vg=initial['vg'],
            nl=initial['nl'],
            ib=initial['ib']
        )


if __name__ == '__main__':
    PlotterCli().run()
