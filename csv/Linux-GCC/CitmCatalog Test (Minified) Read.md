
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2358.93 | 0.0351227 | 5361.84ms | 500299 | 1280 | 6.45973e+06 | 202262 | 0.0351995 | 2.12198 | 9.68451 | 1.72319 | 0.0103747 | 0.00747969 | 0.000114736 | 1(Win) | true |
| Glaze | 1820.67 | 0.0536631 | 6922.61ms | 500299 | 320 | 6.32845e+06 | 262058 | 0.11719 | 2.77161 | 11.6177 | 2.26098 | 0.0140567 | 0.00446565 | 9.99652e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1811.53 | 0.106623 | 6981.34ms | 500299 | 30 | 2.36588e+06 | 263381 | 0.0552483 | 2.78761 | 12.4105 | 2.10464 | 0.0139106 | 0.0397575 | 0.000169699 | 3(Loss) | true |
| simdjson (ondemand) | 1452.49 | 0.148101 | 8630.91ms | 500299 | 160 | 3.78679e+07 | 328487 | 0.0609223 | 3.46329 | 14.2526 | 2.4324 | 0.0170967 | 0.0343719 | 0.000357386 | 4(Loss) | true |
| simdjson (reflection) | 1446.54 | 0.0490053 | 8629.37ms | 500299 | 320 | 8.36056e+06 | 329838 | 0.0462364 | 3.48939 | 14.257 | 2.46033 | 0.0181896 | 0.0219667 | 0.000224291 | 5(Loss) | true |
