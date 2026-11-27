
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1434.1 | 0.191184 | 5330.88ms | 4506446 | 30 | 9.84767e+08 | 2.99679e+06 | 0.601264 | 3.52344 | 16.2308 | 3.13803 | 0.0150526 | 0.0809298 | 0.0100393 | 1(Win) | true |
| simdjson (ondemand) | 935.198 | 0.0928622 | 7789.68ms | 4506446 | 80 | 1.4569e+09 | 4.59548e+06 | 0.368008 | 5.42757 | 21.1824 | 4.39851 | 0.0126638 | 0.0866026 | 0.0100791 | 2(Loss) | true |
