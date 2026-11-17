
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2521.31 | 0.0423148 | 252.953ms | 5839 | 160 | 139.743 | 2208.57 | 0.0175422 | 0.969596 | 1(Win) | true |
| simdjson (ondemand) | 2301.27 | 0.261213 | 253.131ms | 5839 | 2560 | 102276 | 2419.76 | 0.110913 | 1.06408 | 2(Loss) | true |
| simdjson (reflection) | 2235.09 | 0.144048 | 252.467ms | 5839 | 30 | 386.386 | 2491.4 | 0.135314 | 1.09595 | 3(Loss) | true |
| Jsonifier | 1908.86 | 0.217625 | 297.894ms | 5839 | 4890 | 197086 | 2917.2 | 0.524651 | 1.28406 | 4(Loss) | true |
| Glaze | 1845.79 | 0.377236 | 309.379ms | 5839 | 1280 | 165786 | 3016.86 | 0.0780934 | 1.32938 | 5(Loss) | true |
