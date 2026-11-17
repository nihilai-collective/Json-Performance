
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2314.71 | 0.105489 | 786.107ms | 1811 | 2560 | 1585.98 | 746.143 | 0.51225 | 2.33613 | 11.4666 | 1.15075 | 0.000836684 | 4.6806e-05 | 5.39239e-06 | 1(Win) | true |
| simdjson (stage-1) | 893.622 | 0.0855894 | 904.442ms | 1811 | 1280 | 3502.51 | 1932.7 | 0.111442 | 5.86527 | 30.6129 | 2.45555 | 0.00135284 | 9.01608e-05 | 2.15696e-05 | 2(Loss) | true |
