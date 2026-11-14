
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 791.879 | 0.0738288 | 8564.97ms | 4525120 | 80 | 1.29505e+09 | 5.44969e+06 | 0.277329 | 6.46139 | 32.019 | 6.41872 | 0.0155268 | 0.078526 | 0.00383561 | 1(Win) | true |
| simdjson (ondemand) | 612.422 | 0.176385 | 5125.32ms | 4525120 | 40 | 6.17937e+09 | 7.0466e+06 | 0.660624 | 8.30927 | 42.9269 | 8.08853 | 0.0238809 | 0.07834 | 0.00654536 | 2(Loss) | true |
