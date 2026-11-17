
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1552.04 | 0.0709499 | 852.851ms | 2158 | 2560 | 2265.91 | 1326.02 | 0.00285756 | 3.41175 | 12.114 | 2.3202 | 0.000467736 | 8.6162e-05 | 1.66532e-05 | 1(Win) | true |
| simdjson (ondemand) | 1530.02 | 0.0593337 | 856.793ms | 2158 | 4890 | 3114.74 | 1345.1 | 0.0344746 | 3.46173 | 12.1501 | 2.24375 | 0.000467846 | 9.43841e-05 | 2.78604e-05 | 2(Loss) | true |
