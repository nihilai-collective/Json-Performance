
----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14999.7 | 0.152595 | 764.46ms | 6938 | 2560 | 1159.92 | 441.116 | 0.085971 | 0.373352 | 1.05967 | 0.164889 | 0.000144528 | 2.10007e-05 | 8.50164e-06 | 1(Win) | true |
| Glaze | 2980.63 | 0.197242 | 952.076ms | 6960 | 2560 | 49390 | 2226.9 | 0.160192 | 1.74985 | 4.28635 | 0.706609 | 0.000288928 | 2.94091e-05 | 6.56654e-06 | 2(Loss) | true |
| simdjson (reflection) | 504.252 | 0.11779 | 2056.81ms | 6938 | 2560 | 611545 | 13121.6 | 0.0270681 | 10.043 | 38.7181 | 7.2557 | 0.00700372 | 0.000121219 | 6.43535e-05 | 3(Loss) | true |
