
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 795.855 | 1.24811 | 5254.67ms | 676745 | 80 | 8.19551e+09 | 810945 | 0.381732 | 3.11068 | 1(Win) | true |
| simdjson (ondemand) | 380.867 | 0.150497 | 5310.72ms | 676745 | 30 | 1.9511e+08 | 1.69454e+06 | 0.518846 | 6.50028 | 2(Loss) | true |
