
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12453.3 | 0.0294486 | 4600.82ms | 500299 | 1280 | 162941 | 38313 | 0.148198 | 0.405794 | 1.81572 | 0.301818 | 0.00139568 | 0.00516246 | 2.54535e-06 | 1(Win) | true |
| simdjson (reflection) | 11199.6 | 0.0534562 | 4999.15ms | 500299 | 320 | 165959 | 42601.7 | 0.0386499 | 0.451211 | 2.18113 | 0.197082 | 0.00135663 | 0.000417026 | 1.45788e-05 | 2(Loss) | true |
| Glaze | 5912.76 | 0.0490694 | 8851.14ms | 500299 | 2560 | 4.01365e+06 | 80693.6 | 0.0311072 | 0.839645 | 3.76516 | 0.550621 | 0.00150804 | 0.0236324 | 2.09882e-05 | 3(Loss) | true |
