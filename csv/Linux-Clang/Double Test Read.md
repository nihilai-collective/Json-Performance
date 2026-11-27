
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 720.199 | 0.0487428 | 963.189ms | 1811 | 4890 | 6681.31 | 2398.09 | 0.172889 | 7.22862 | 36.2684 | 7.56764 | 0.000599043 | 9.28206e-05 | 1.8406e-05 | 1(Win) | true |
| simdjson (ondemand) | 438.944 | 0.0471815 | 1110.9ms | 1811 | 2560 | 8822.74 | 3934.68 | 0.161487 | 11.8124 | 59.291 | 11.4395 | 0.00174498 | 0.000117554 | 3.1923e-05 | 2(Loss) | true |
