
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2036.35 | 0.282147 | 883.112ms | 2632 | 30 | 362.861 | 1232.63 | 0.00270431 | 2.60581 | 10.0828 | 1.88108 | 0.00158308 | 2.53293e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1569.07 | 0.105306 | 888.09ms | 2632 | 1280 | 3632.48 | 1599.72 | 0.249394 | 3.31551 | 11.6052 | 2.14058 | 0.00205523 | 9.14229e-05 | 3.85876e-05 | 2(Loss) | true |
