
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1528.03 | 0.123625 | 9997.2ms | 4212000 | 40 | 4.22462e+08 | 2.6288e+06 | 0.343174 | 3.31925 | 15.1672 | 2.91952 | 0.012493 | 0.0665467 | 0.00667105 | 1(Win) | true |
| simdjson (ondemand) | 1325.11 | 0.139076 | 5471.97ms | 4212000 | 40 | 7.10948e+08 | 3.03135e+06 | 0.403867 | 3.85086 | 15.6689 | 2.91446 | 0.0133619 | 0.066385 | 0.00288332 | 2(Loss) | true |
