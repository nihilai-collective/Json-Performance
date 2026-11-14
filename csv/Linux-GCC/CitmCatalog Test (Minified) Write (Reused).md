
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12499.8 | 0.14749 | 4571.92ms | 500299 | 80 | 253552 | 38170.4 | 0.0110373 | 0.404368 | 1.81463 | 0.301572 | 0.0015092 | 0.00217133 | 1.32671e-05 | 1(Win) | true |
| simdjson (reflection) | 11365.5 | 0.0380969 | 4956.34ms | 500299 | 1280 | 327395 | 41979.9 | 0.0509953 | 0.444755 | 2.18004 | 0.196834 | 0.00110444 | 0.000996167 | 9.42874e-06 | 2(Loss) | true |
| Glaze | 7167.9 | 0.0335374 | 7421.76ms | 500299 | 1280 | 637890 | 66563.8 | 0.0415699 | 0.705271 | 3.75128 | 0.547385 | 0.0015815 | 0.000883528 | 2.03238e-05 | 3(Loss) | true |
