
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1234.02 | 0.072095 | 1484.27ms | 9739 | 640 | 18844.1 | 7526.49 | 0.00965247 | 4.19381 | 17.6537 | 3.52993 | 0.00395607 | 2.77557e-05 | 6.89881e-06 | 1(Win) | true |
| simdjson (ondemand) | 829.489 | 0.108424 | 1854.64ms | 9739 | 40 | 5895.48 | 11197 | 0.403679 | 6.23369 | 29.8189 | 5.72749 | 0.00762655 | 2.8237e-05 | 2.567e-06 | 2(Loss) | true |
