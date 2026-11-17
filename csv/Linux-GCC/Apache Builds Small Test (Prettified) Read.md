
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2363.52 | 0.0553031 | 889.607ms | 3370 | 4890 | 2765.34 | 1359.78 | 0.192166 | 2.22428 | 8.95519 | 1.56499 | 0.000695114 | 4.53903e-05 | 6.97845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1946.49 | 0.0815768 | 888.97ms | 3370 | 2560 | 4644.4 | 1651.12 | 0.017575 | 2.68669 | 9.39881 | 1.68457 | 0.00261429 | 4.47422e-05 | 1.13594e-05 | 2(Loss) | true |
