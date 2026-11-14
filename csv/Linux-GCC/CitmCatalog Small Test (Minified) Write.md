
----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7568.16 | 0.0760335 | 768.5ms | 3223 | 4890 | 466.293 | 406.135 | 0.266503 | 0.739384 | 2.07633 | 0.343779 | 0.000310333 | 6.49092e-05 | 3.55954e-05 | 1(Win) | true |
| simdjson (reflection) | 6084.62 | 0.113631 | 778.304ms | 3223 | 4890 | 1611.22 | 505.158 | 0.0181099 | 0.902674 | 2.6829 | 0.320509 | 0.000311158 | 4.89199e-05 | 2.47455e-05 | 2(Loss) | true |
| Glaze | 3402.2 | 0.122351 | 821.723ms | 3223 | 2560 | 3127.94 | 903.442 | 0.101755 | 1.55413 | 4.94663 | 0.755818 | 0.000310997 | 0.000106655 | 6.01148e-05 | 3(Loss) | true |
