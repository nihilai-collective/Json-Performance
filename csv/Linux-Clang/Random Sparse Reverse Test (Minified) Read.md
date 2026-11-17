
----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1879.65 | 0.0315313 | 5516.6ms | 409725 | 640 | 2.74977e+06 | 207881 | 0.181877 | 2.73195 | 12.84 | 2.46704 | 0.00846379 | 0.000283174 | 6.56309e-06 | 1(Win) | true |
| simdjson (ondemand) | 1465.87 | 0.0827954 | 6990.39ms | 409725 | 160 | 7.79339e+06 | 266561 | 0.114474 | 3.48083 | 15.3706 | 2.62642 | 0.0120128 | 0.00287974 | 1.87626e-06 | 2(Loss) | true |
