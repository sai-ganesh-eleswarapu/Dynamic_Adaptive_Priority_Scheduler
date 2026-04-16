# DAPS — Dynamic Adaptive Priority Scheduler

Overview
DAPS is a fair resource allocation system designed to improve CPU scheduling in operating systems. It uses dynamic priorities and an aging mechanism to prevent starvation and ensure balanced execution of processes.

Problem Statement
Traditional priority scheduling suffers from **STARVATION**, where low-priority processes may never get CPU time.
- High-priority processes dominate execution  
- Low-priority processes wait indefinitely  
- Leads to unfair resource allocation  

Proposed Solution (DAPS)
DAPS introduces:

- Preemptive Priority Scheduling
- Aging Mechanism (increases priority of waiting processes)
- Dynamic Priority Adjustment
This ensures fairness and prevents starvation.

Working of the Algorithm
1. Select process with highest priority  
2. Execute for 1 time unit (preemptive)  
3. Increase priority of waiting processes (aging)  
4. Repeat until all processes complete  

System Architecture
- Backend: C (Scheduling logic)
- Frontend: Streamlit (UI visualization)
- Input: File-based process data
- Output: Waiting time, turnaround time, Gantt chart

Features
- Fair CPU scheduling  
- Prevents starvation  
- Dynamic priority adjustment  
- Gantt chart visualization  
- Simple and interactive UI  

How to Run
1. Compile backend:
   ```bash
   gcc scheduler.c -o scheduler

2. Run Streamlit app
   streamlit run app/app.py by opening main folder (DAPS) as integrated terminal
