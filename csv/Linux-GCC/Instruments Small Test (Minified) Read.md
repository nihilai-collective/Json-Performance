
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1526.93 | 0.117292 | 1012.79ms | 4669 | 40 | 467.958 | 2916.12 | 0.0893652 | 3.41834 | 13.7406 | 2.76783 | 0.00171878 | 9.10259e-05 | 8.0317e-05 | 1(Win) | true |
| simdjson (ondemand) | 1498.49 | 0.0465043 | 1020.9ms | 4669 | 2560 | 4888.38 | 2971.46 | 0.206224 | 3.47139 | 15.211 | 2.49177 | 0.000431453 | 2.96169e-05 | 8.53368e-06 | 2(Loss) | true |
