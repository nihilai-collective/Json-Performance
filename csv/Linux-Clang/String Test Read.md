
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 944.108 | 0.101314 | 1149.08ms | 4215 | 1280 | 23817.8 | 4257.71 | 0.635515 | 5.4818 | 24.0754 | 4.3497 | 0.00349496 | 3.92942e-05 | 6.3019e-06 | 1(Win) | true |
| Jsonifier (generic) | 695.148 | 0.0541122 | 1298.96ms | 4215 | 1280 | 12532.6 | 5782.56 | 0.0444296 | 7.47988 | 27.2289 | 5.57058 | 0.00334723 | 4.37426e-05 | 1.26038e-05 | 2(Loss) | true |
