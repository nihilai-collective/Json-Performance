
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 889.615 | 0.143106 | 8073.91ms | 4506446 | 30 | 1.43383e+09 | 4.83095e+06 | 0.374121 | 5.72542 | 26.2142 | 5.36734 | 0.0157227 | 0.0813325 | 0.0031503 | 1(Win) | true |
| simdjson (ondemand) | 474.965 | 0.107768 | 6688.78ms | 4506446 | 40 | 3.80352e+09 | 9.04842e+06 | 0.0772185 | 10.6903 | 46.9802 | 8.44709 | 0.0325375 | 0.0867631 | 0.0161198 | 2(Loss) | true |
