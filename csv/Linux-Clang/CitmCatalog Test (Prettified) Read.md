
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15194.9 | 0.152992 | 8113.02ms | 1151920 | 40 | 489380 | 72297.5 | 0.490784 | 0.337323 | 1.86187 | 0.113597 | 0.000392931 | 0.0029621 | 1.38899e-06 | 1(Win) | true |
| simdjson (stage-1) | 13928.4 | 0.15466 | 8750.73ms | 1151920 | 30 | 446392 | 78871.7 | 0.288598 | 0.368913 | 1.738 | 0.0731284 | 0.00017316 | 0.00348708 | 4.48527e-06 | 2(Loss) | true |
