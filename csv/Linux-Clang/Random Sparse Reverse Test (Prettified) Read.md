
----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2639.36 | 0.110394 | 6361.71ms | 676745 | 40 | 2.91474e+06 | 244527 | 0.130249 | 1.91728 | 8.49114 | 1.55262 | 0.00648376 | 0.000494943 | 8.23796e-06 | 1(Win) | true |
| simdjson (ondemand) | 2320.34 | 0.0262188 | 7308.23ms | 676745 | 1280 | 6.80742e+06 | 278147 | 0.0418755 | 2.20784 | 9.7427 | 1.60045 | 0.00782886 | 0.00255256 | 4.99057e-06 | 2(Loss) | true |
