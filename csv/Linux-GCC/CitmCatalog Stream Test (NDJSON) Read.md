
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1664.26 | 0.120808 | 8719.68ms | 4525120 | 30 | 2.94394e+08 | 2.59303e+06 | 0.0296001 | 3.06316 | 15.2795 | 2.75502 | 0.00956783 | 0.0774521 | 0.000952726 | 1(Win) | true |
| simdjson (ondemand) | 1408.35 | 0.0824122 | 10202.4ms | 4525120 | 80 | 5.10163e+08 | 3.06421e+06 | 0.173854 | 3.61084 | 16.3054 | 2.60332 | 0.0149448 | 0.0769058 | 0.00168662 | 2(Loss) | true |
