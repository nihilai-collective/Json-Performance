
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2052.43 | 0.0375973 | 1099.14ms | 8150 | 4890 | 9912.93 | 3786.95 | 0.19481 | 2.53408 | 10.5702 | 1.93436 | 0.00283187 | 2.05503e-05 | 3.28704e-06 | 1(Win) | true |
| simdjson (ondemand) | 1717.9 | 0.0801671 | 1173.18ms | 8150 | 160 | 2104.91 | 4524.39 | 0.0205786 | 3.02714 | 11.6629 | 2.08994 | 0.00257285 | 3.68098e-05 | 1.38037e-05 | 2(Loss) | true |
