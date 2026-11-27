
----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1530.36 | 0.133334 | 892.997ms | 2632 | 1280 | 6121.82 | 1640.19 | 0.0919874 | 3.44356 | 14.1284 | 2.7595 | 0.0045655 | 4.63051e-05 | 1.12794e-05 | 1(Win) | true |
| simdjson (ondemand) | 775.414 | 0.0622005 | 1052.1ms | 2632 | 2560 | 10378.4 | 3237.07 | 0.122549 | 6.71759 | 29.1128 | 5.4943 | 0.0112306 | 0.000132385 | 7.59878e-05 | 2(Loss) | true |
