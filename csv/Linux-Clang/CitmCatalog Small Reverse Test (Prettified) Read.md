
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1189.78 | 0.0259996 | 1505.14ms | 9739 | 2560 | 10545.5 | 7806.34 | 0.0248384 | 4.35461 | 18.2056 | 3.58475 | 0.00331235 | 3.66599e-05 | 1.42789e-05 | 1(Win) | true |
| simdjson (ondemand) | 846.194 | 0.0316818 | 1818.14ms | 9739 | 1280 | 15478.2 | 10976 | 0.00467661 | 6.11153 | 29.7888 | 5.72379 | 0.0070436 | 2.18997e-05 | 3.77028e-06 | 2(Loss) | true |
