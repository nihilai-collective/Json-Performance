
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1303.81 | 0.353556 | 5772ms | 4506446 | 30 | 4.07452e+09 | 3.29624e+06 | 0.320905 | 1.89884 | 1(Win) | true |
| simdjson (ondemand) | 1106.46 | 0.0635923 | 6689.77ms | 4506446 | 30 | 1.83032e+08 | 3.88418e+06 | 0.977428 | 2.23755 | 2(Loss) | true |
