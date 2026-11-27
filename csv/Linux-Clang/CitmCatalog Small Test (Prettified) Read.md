
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2054.21 | 0.0528048 | 1181.75ms | 9739 | 2560 | 14592.3 | 4521.36 | 0.0692153 | 2.50581 | 10.4031 | 1.80635 | 0.00145324 | 2.95205e-05 | 5.37465e-06 | 1(Win) | true |
| simdjson (ondemand) | 2050.78 | 0.0446026 | 1177.54ms | 9739 | 2560 | 10446 | 4528.93 | 0.0081255 | 2.53254 | 10.3751 | 1.67194 | 0.00165904 | 4.49225e-05 | 2.06162e-05 | 2(Loss) | true |
