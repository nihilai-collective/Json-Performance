
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2369.73 | 0.0959526 | 5468.96ms | 500299 | 30 | 1.11969e+06 | 201341 | 0.214449 | 2.13156 | 9.6841 | 1.72307 | 0.0102385 | 0.00685717 | 8.1951e-05 | 1(Win) | true |
| Glaze | 1817.44 | 0.169185 | 6971.17ms | 500299 | 30 | 5.91814e+06 | 262524 | 0.0362756 | 2.77922 | 11.6164 | 2.26096 | 0.0139762 | 0.00536939 | 8.83472e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1791.48 | 0.482113 | 7059.09ms | 500299 | 640 | 1.05515e+09 | 266329 | 0.308448 | 2.82026 | 12.4106 | 2.10465 | 0.0141155 | 0.0435427 | 0.0001939 | 3(Loss) | true |
| simdjson (ondemand) | 1430.32 | 0.383676 | 8753.81ms | 500299 | 1280 | 2.09668e+09 | 333578 | 0.00360988 | 3.53254 | 14.2457 | 2.43024 | 0.016296 | 0.0369765 | 0.000218957 | 4(Loss) | true |
| simdjson (reflection) | 1404.44 | 0.803431 | 8959.41ms | 500299 | 80 | 5.95991e+08 | 339724 | 0.184229 | 3.59715 | 14.2443 | 2.44673 | 0.017745 | 0.024718 | 8.23508e-05 | 5(Loss) | true |
