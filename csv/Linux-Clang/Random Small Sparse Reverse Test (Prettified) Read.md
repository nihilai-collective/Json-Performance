
----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2780.7 | 0.0515777 | 998.084ms | 8150 | 2560 | 5320.73 | 2795.14 | 0.0246181 | 1.87793 | 7.99718 | 1.45031 | 0.00222522 | 2.19517e-05 | 4.16986e-06 | 1(Win) | true |
| simdjson (ondemand) | 2526.73 | 0.0777212 | 1023.48ms | 8150 | 1280 | 7316.21 | 3076.09 | 0.0333358 | 2.06407 | 9.22699 | 1.48454 | 0.00249406 | 9.39417e-06 | 2.87577e-07 | 2(Loss) | true |
