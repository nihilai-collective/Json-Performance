
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 800.675 | 0.0284026 | 1266.38ms | 4630 | 4890 | 11997 | 5514.74 | 0.0926792 | 6.51375 | 31.3054 | 5.75076 | 0.00308511 | 3.72338e-05 | 7.46443e-06 | 1(Win) | true |
| Jsonifier (generic) | 719.148 | 0.117451 | 1337.59ms | 4630 | 40 | 2080.17 | 6139.93 | 0.111826 | 7.34338 | 31.5624 | 6.42765 | 0.0107235 | 0.00012419 | 3.23974e-05 | 2(Loss) | true |
