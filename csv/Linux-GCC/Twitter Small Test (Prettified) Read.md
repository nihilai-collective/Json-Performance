
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2796.65 | 0.0813256 | 847.786ms | 3770 | 160 | 174.897 | 1285.59 | 0.0393942 | 1.89739 | 7.22546 | 1.22653 | 0.00026691 | 2.32095e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2644.76 | 0.119772 | 856.16ms | 3770 | 160 | 424.17 | 1359.42 | 0.227635 | 2.00691 | 7.45809 | 1.17613 | 0.000303382 | 8.12334e-05 | 1.98939e-05 | 2(Loss) | true |
