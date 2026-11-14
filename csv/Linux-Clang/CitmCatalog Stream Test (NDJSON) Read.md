
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1489.14 | 0.11084 | 9663.64ms | 4525120 | 30 | 3.09534e+08 | 2.89798e+06 | 0.209729 | 3.40428 | 16.6405 | 3.0144 | 0.00957328 | 0.0777589 | 0.000684777 | 1(Win) | true |
| simdjson (ondemand) | 1332.22 | 0.0577866 | 5170.15ms | 4525120 | 80 | 2.8032e+08 | 3.23933e+06 | 0.131783 | 3.79387 | 17.1962 | 2.62393 | 0.0135537 | 0.0774928 | 0.00179199 | 2(Loss) | true |
