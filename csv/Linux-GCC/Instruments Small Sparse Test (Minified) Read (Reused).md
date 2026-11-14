
----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4943.67 | 0.0627109 | 801.087ms | 4669 | 320 | 102.09 | 900.688 | 0.144818 | 1.10609 | 4.93639 | 0.682587 | 0.00115656 | 1.87406e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4662.14 | 0.0503002 | 806.556ms | 4669 | 320 | 73.8528 | 955.078 | 0.0147261 | 1.15064 | 5.3052 | 0.641893 | 0.00107089 | 1.80713e-05 | 4.68516e-06 | 2(Loss) | true |
