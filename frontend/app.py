# Improved the Streamlit visualisation.

import streamlit as st
import subprocess
import pandas as pd
import matplotlib.pyplot as plt

st.title("DAPS Scheduler 🚀")

if st.button("Run Scheduler"):

    # Run backend
    subprocess.run(["..\\backend\\scheduler.exe"], shell=True)

    # ---------- INPUT TABLE ----------
    lines = open("..\\data\\input.txt").readlines()
    n = int(lines[0])

    input_data = [list(map(int, lines[i].split())) for i in range(1, n+1)]
    df_input = pd.DataFrame(input_data, columns=["PID", "Arrival Time", "Burst Time", "Priority"])

    st.subheader("Input Processes")
    st.table(df_input)

    # ---------- OUTPUT TABLE ----------
    lines = open("..\\data\\output.txt").readlines()

    result_data = []
    for i in range(len(lines)):
        if "PID" in lines[i]:
            j = i + 1
            while j < len(lines) and lines[j].strip():
                result_data.append(list(map(int, lines[j].split())))
                j += 1
            break

    df_result = pd.DataFrame(result_data, columns=["PID", "Waiting Time", "Turnaround Time"])

    st.subheader("Scheduling Results")
    st.table(df_result)

    # GANTT CHART

    st.subheader("Process Execution Visualisation")

    gantt_line = [l.strip() for l in lines if "P" in l][-1]
    gantt = gantt_line.split()

    # Compress
    gantt_data = []
    start = 0

    for i in range(1, len(gantt)):
        if gantt[i] != gantt[i-1]:
            gantt_data.append((gantt[i-1], start, i))
            start = i

    gantt_data.append((gantt[-1], start, len(gantt)))

    # 🎨 Color mappings
    unique_processes = list(set(gantt))

    # Generate colors automatically
    colors = plt.cm.tab10(range(len(unique_processes)))

    # Map process → color
    color_map = dict(zip(unique_processes, colors))

    # -------- PLOT --------
    fig, ax = plt.subplots()

    y = 0

    for process, start, end in gantt_data:
        ax.barh(
            y,
            end - start,
            left=start,
            color=color_map.get(process, "gray")  # default if new process
        )

        ax.text(
            start + (end-start)/2,
            y,
            process,
            ha='center',
            va='center',
            color='black'
        )

    # Axis
    ax.set_xlabel("Time")
    ax.set_yticks([])

    # Show exact boundaries
    times = [start for _, start, _ in gantt_data] + [gantt_data[-1][2]]
    ax.set_xticks(times)

    st.pyplot(fig)
