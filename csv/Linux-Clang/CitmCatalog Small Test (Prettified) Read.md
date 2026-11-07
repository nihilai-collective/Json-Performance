
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2730.51 | 0.11878 | 218.565ms | 5839 | 30 | 176.033 | 2039.37 | 0.0474228 | 0.895456 | 1(Win) | true |
| Jsonifier | 1913.17 | 0.23646 | 290.146ms | 5839 | 2560 | 121262 | 2910.62 | 0.361364 | 1.28156 | 2(Loss) | true |
| simdjson (ondemand) | 1897.36 | 0.135757 | 296.442ms | 5839 | 40 | 634.984 | 2934.88 | 0.0746209 | 1.29387 | 3(Loss) | true |
| Glaze | 1850.06 | 0.177572 | 309.534ms | 5839 | 30 | 856.99 | 3009.9 | 0.0786913 | 1.32575 | 4(Loss) | true |
