
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2123.35 | 0.277611 | 6678.85ms | 4219120 | 30 | 8.30225e+08 | 1.89496e+06 | 0.424287 | 1.16596 | 1(Win) | true |
| Jsonifier (generic) | 1936.43 | 0.225316 | 7355.54ms | 4219120 | 30 | 6.57579e+08 | 2.07788e+06 | 0.15323 | 1.27852 | 2(Loss) | true |
