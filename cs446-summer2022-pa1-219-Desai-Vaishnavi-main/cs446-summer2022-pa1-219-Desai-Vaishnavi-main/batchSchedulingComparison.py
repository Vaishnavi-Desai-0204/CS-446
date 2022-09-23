# sys.argv
import sys
import os.path
from os import path

def main():
    order = []
    completion = []
    
    if len(sys.argv) == 3:
        filename = sys.argv[1]
        status = path.isfile(filename)
        if (status == False):
            print("Input batchfile not found!")
            return 1
        elif (status == True):
            
            with open(filename) as f:
                array = []
                for line in f: # read rest of lines
                    array.append([int(x) for x in line.split(', ')])
                f.close()
                
            n = len(array)
            burst = []
            for i in range(n): 
                burst.append(array[i][2])
            arrival = []
            for i in range(n): 
                arrival.append(array[i][1])
            avgw = 0 
            avgt = 0 
            turnaround = []
            wait = []
            if (sys.argv[2] == "Priority"):
                order,completion = PrioritySort(array)
                print("PID ORDER OF EXECUTION: \n")
                for g in range(len(order)):
                    print(order[g][0])
                avgw , avgt , wait , turnaround = ComputeStats(completion , arrival, burst)
                print("\nAverage Process Turnaround Time:", avgt)
                print("Average Process Wait Time:", avgw)
                
            elif (sys.argv[2] == "ShortestRemaining"):
                order,completion = ShortestRemaining(array)
                print("PID ORDER OF EXECUTION: \n")
                for g in range(len(order)):
                    print(order[g][0])
                avgw , avgt , wait , turnaround = ComputeStats(completion , arrival, burst)
                print("\nAverage Process Turnaround Time:", avgt)
                print("Average Process Wait Time:" , avgw)
            else :
                print("Unidentified sorting algorithm. Please input either ShortestRemaining or Priority.")
                return 1
    else:
        print("Please provide command line arguments when running.\npython3 batchSchedulingComparison.py batchfile.txt Priority")
        return 1

def ShortestRemaining(proc):
    current_time = 0
    completed = 0
    complete = []
    n = len(proc)
    burst = []
    for i in range(n): 
        burst.append(proc[i][2])
    completion_time = [0] * n
    prev = 0
    is_completed = [0] * n
    
    while (completed != n):
        idx = -1
        mn = 10000000
        
        for i in range(n):
            if(proc[i][1] <= current_time and is_completed[i] == 0):
                if(burst[i] < mn):
                    mn = burst[i]
                    idx = i
            if (burst[i] == mn):
                if(proc[i][1] < proc[idx][1]):
                    mn = burst[i]
                    idx = i
        
        if(idx != -1):
            complete.append(proc[idx])
            burst[idx] -= 1
            current_time += 1
            if(burst[idx] == 0):
                completion_time[idx] = current_time
                is_completed[idx] = 1
                completed +=1 
        else:
            current_time +=1
    PID = []
    prev = 0;
    for i in range(len(complete)):
        if(complete[i][0] != prev):
            prev = complete[i][0]
            PID.append(complete[i])
    return PID, completion_time
    
def PrioritySort(proc):
    current_time = 0
    completed = 0
    complete = []
    n = len(proc)
    burst = []
    for i in range(n): 
        burst.append(proc[i][2])
    start_time = [0] * n
    completion_time = [0] * n
    prev = 0
    is_completed = [0] * n
    
    while (completed != n):
        idx = -1
        mx = 1000000
        
        for i in range(n):
            if(proc[i][1] <= current_time and is_completed[i] == 0):
                if(proc[i][3] < mx):
                    mx = proc[i][3]
                    idx = i
                if (proc[i][3] == mx):
                    if(proc[i][1] < proc[idx][1]):
                        mx = proc[i][3]
                        idx = i
                    if(proc[i][1] == proc[idx][1]):
                        if(proc[i][0] < proc[idx][0]):
                            mx = proc[i][3]
                            idx = i
        
        if(idx != -1):
            complete.append(proc[idx])
            start_time[idx] = current_time
            completion_time[idx] = start_time[idx] + proc[idx][2]
            is_completed[idx] = 1
            completed +=1 
            current_time = completion_time[idx]
            
        else:
            current_time +=1
    return complete, completion_time

def ComputeStats(completion , arrival , burst):
    n = len(burst)
    add1 = 0
    add2 = 0
    averagewait = 0 
    averagturnaround = 0 
    turnaround = []
    wait = []
    
    for i in range(n): 
        turnaround.append(completion[i] - arrival[i])
        add1 += turnaround[i]
        wait.append(turnaround[i] - burst[i])
        add2 += wait[i]
    
    averagturnaround = add1 / n
    averagewait  = add2 / n
    
    return averagewait , averagturnaround , wait , turnaround
if __name__=="__main__":
    main()
