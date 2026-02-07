#speed comparision between single thread and multi threads and mutli process for cpu bound oprtaion works

import time
import threading
import multiprocessing as mp

def cpu_bound(x):
    return sum(i * i for i in range(10**7))

import time
import threading
import multiprocessing as mp

def cpu_bound(x):
    return sum(i * i for i in range(10**7))


# Anything here runs every time a child process is born.

if __name__ == '__main__':
    data = range(32)

    # 1. Single-threaded
    start = time.time()
    results_single = [cpu_bound(x) for x in data]
    print(f"Single-threaded:          {time.time() - start:6.2f} seconds")

    # 2. Threading
    def thread_task(idx, val, results):
        results[idx] = cpu_bound(val)

    start = time.time()
    threads = []
    results_thread = [None] * len(data)
    for i, x in enumerate(data):
        t = threading.Thread(target=thread_task, args=(i, x, results_thread))
        threads.append(t)
        t.start()
    for t in threads:
        t.join()
    print(f"Threading (32 threads):   {time.time() - start:6.2f} seconds")

    # 3. Multiprocessing
    num_processes = mp.cpu_count()
    print(f"Running with {num_processes} processes...")
    start = time.time()
    with mp.Pool(processes=num_processes) as pool:
        results_mp = pool.map(cpu_bound, data)
    print(f"Multiprocessing ({num_processes} processes): {time.time() - start:6.2f} seconds")