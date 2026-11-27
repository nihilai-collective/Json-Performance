
----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1462.61 | 0.0829311 | 9732.1ms | 1151920 | 160 | 6.20787e+07 | 751094 | 0.33582 | 3.48874 | 16.5401 | 3.35417 | 0.0100732 | 0.0418588 | 8.79239e-05 | 1(Win) | true |
| simdjson (ondemand) | 916.288 | 0.0671582 | 7649.49ms | 1151920 | 160 | 1.03729e+08 | 1.19892e+06 | 0.426951 | 5.53637 | 29.1272 | 5.70398 | 0.0147532 | 0.0862645 | 5.29117e-05 | 2(Loss) | true |
