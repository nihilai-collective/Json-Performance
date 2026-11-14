
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 722.339 | 0.0987072 | 8847.59ms | 4219119 | 30 | 9.06944e+08 | 5.57033e+06 | 0.160628 | 7.05242 | 27.2144 | 5.16607 | 0.0199981 | 0.0569846 | 7.22505e-05 | 1(Win) | true |
| simdjson (ondemand) | 313.338 | 0.344183 | 9215.26ms | 4219119 | 30 | 5.86029e+10 | 1.28413e+07 | 0.228224 | 16.102 | 64.3696 | 13.2909 | 0.0866732 | 0.0573884 | 0.0097863 | 2(Loss) | true |
