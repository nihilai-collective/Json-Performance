
----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3364.67 | 0.0520861 | 846.303ms | 4669 | 320 | 152.04 | 1323.37 | 0.0333067 | 1.5769 | 7.22082 | 1.2643 | 0.00138547 | 2.74416e-05 | 2.00792e-06 | 1(Win) | true |
| simdjson (ondemand) | 2616.47 | 0.601817 | 877.792ms | 4669 | 30 | 3146.79 | 1701.8 | 0.0117509 | 2.01903 | 9.21782 | 1.49325 | 0.00262012 | 5.71143e-05 | 2.14179e-05 | 2(Loss) | true |
