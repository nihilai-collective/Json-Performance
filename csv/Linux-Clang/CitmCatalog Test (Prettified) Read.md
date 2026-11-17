
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2513.9 | 0.680535 | 5654.12ms | 1151920 | 640 | 5.66016e+09 | 436993 | 0.243971 | 2.01221 | 8.58617 | 1.51224 | 0.00684247 | 0.0343918 | 2.58522e-05 | 1(Win) | true |
| simdjson (ondemand) | 2395.93 | 0.0450231 | 5991.73ms | 1151920 | 640 | 2.72738e+07 | 458509 | 0.290042 | 2.11532 | 8.78977 | 1.33834 | 0.0103086 | 0.0356868 | 3.58545e-05 | 2(Loss) | true |
