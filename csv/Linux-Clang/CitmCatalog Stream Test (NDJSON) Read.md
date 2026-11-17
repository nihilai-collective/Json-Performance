
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1464.09 | 0.149531 | 9908.45ms | 4525120 | 40 | 7.77043e+08 | 2.94755e+06 | 0.277695 | 3.49552 | 16.6413 | 3.01451 | 0.00950586 | 0.0778435 | 0.0038786 | 1(Win) | true |
| simdjson (ondemand) | 1307.65 | 0.184272 | 5260.21ms | 4525120 | 30 | 1.10948e+09 | 3.30019e+06 | 0.622801 | 3.87162 | 17.208 | 2.6279 | 0.0154574 | 0.0776282 | 0.0131329 | 2(Loss) | true |
