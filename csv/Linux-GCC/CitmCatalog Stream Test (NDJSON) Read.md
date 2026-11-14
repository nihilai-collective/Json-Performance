
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1649.62 | 0.0822842 | 8774.2ms | 4525120 | 80 | 3.70691e+08 | 2.61604e+06 | 0.00897267 | 3.07572 | 15.2833 | 2.75497 | 0.00975861 | 0.0776958 | 0.000753662 | 1(Win) | true |
| simdjson (ondemand) | 1429.41 | 0.0712559 | 10042.6ms | 4525120 | 30 | 1.38839e+08 | 3.01908e+06 | 0.0167993 | 3.53501 | 16.307 | 2.60221 | 0.0123075 | 0.0769295 | 0.00128963 | 2(Loss) | true |
