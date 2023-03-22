#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os
from typing import Dict, List, Tuple, Optional
import pprint
import json

LOG_FOLDER = "../logs"
Values = List[Tuple[int, float]]
Data = Dict[str, Values]
Log = Dict[str, Data]


def parse() -> Optional[Log]:
    if os.path.exists(LOG_FOLDER) and os.path.isdir(LOG_FOLDER):
        logs: Log = {}
        for file_name in os.listdir(LOG_FOLDER):
            path = os.path.join(LOG_FOLDER, file_name)
            if os.path.isfile(path):
                with open(path, "r") as file:
                    contents = file.readlines()
                data: Data = {}
                for i in range(0, len(contents), 3):
                    game_string = contents[i].strip()
                    values = data.setdefault(game_string, [])
                    values.append((int(contents[i + 1].strip()), float(contents[i + 2].strip())))
                logs[file_name.replace(".log", "")] = data
        json.dump(logs, open(os.path.join(LOG_FOLDER, "data.json"), "w"), indent=2)
        pprint.pprint(logs)
        print("Logs parsed and saved to data.json")
        return logs
    else:
        print("No logs found")
        return


def plot(logs: Log):
    algorithms = list(logs.keys())
    game_strings = list(logs[algorithms[0]].keys())
    for game_string in game_strings:
        print(f"Game: {game_string}")
        for algorithm in algorithms:
            values = logs[algorithm][game_string]
            max_mem = max(values, key=lambda x: x[0])[0]
            max_time = max(values, key=lambda x: x[1])[1]
            min_mem = min(values, key=lambda x: x[0])[0]
            min_time = min(values, key=lambda x: x[1])[1]
            avg_mem = round(sum([x[0] for x in values]) / len(values))
            avg_time = round(sum([x[1] for x in values]) / len(values))
            print(f"{algorithm}: \n"
                  f"\tavg: {avg_mem} B, {avg_time} ms\n"
                  f"\tmin: {min_mem} B, {min_time} ms\n"
                  f"\tmax: {max_mem} B, {max_time} ms")
        print()


def main():
    logs: Log
    if os.path.exists(LOG_FOLDER) and os.path.isdir(LOG_FOLDER):
        parsed_file_path = os.path.join(LOG_FOLDER, "data.json")
        if os.path.exists(parsed_file_path) and os.path.isfile(parsed_file_path):
            logs = json.load(open(parsed_file_path, "r"))
        else:
            logs = parse()
    else:
        logs = parse()
    if logs is not None:
        plot(logs)


if __name__ == '__main__':
    main()
