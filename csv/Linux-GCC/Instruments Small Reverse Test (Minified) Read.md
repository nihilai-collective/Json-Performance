
----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 560.693 | 0.06195 | 1520.24ms | 4669 | 640 | 15490.3 | 7941.43 | 0.0994187 | 9.22827 | 39.072 | 7.81238 | 0.00971501 | 2.67723e-05 | 2.00792e-06 | 1(Win) | true |
| simdjson (ondemand) | 242.853 | 0.0615102 | 2564.58ms | 4669 | 320 | 40701.1 | 18335 | 0.0152566 | 21.2371 | 94.8042 | 19.3697 | 0.0500033 | 3.27961e-05 | 4.68516e-06 | 2(Loss) | true |
