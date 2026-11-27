
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1702.9 | 0.192292 | 788.337ms | 1213 | 2560 | 4368.25 | 679.315 | 0.13099 | 3.20847 | 16.0503 | 2.9258 | 0.00152128 | 0.00037871 | 0.000174863 | 1(Win) | true |
| Glaze | 994.496 | 0.155743 | 835.321ms | 1213 | 2560 | 8401.8 | 1163.21 | 0.311437 | 5.36009 | 26.8368 | 3.83512 | 0.00216534 | 0.000213185 | 7.11691e-05 | 2(Loss) | true |
| simdjson (ondemand) | 353.25 | 0.19422 | 1051.18ms | 1213 | 320 | 12944.8 | 3274.75 | 0.027094 | 14.759 | 59.2787 | 12.0322 | 0.0114746 | 0.000157152 | 2.57626e-05 | 3(Loss) | true |
