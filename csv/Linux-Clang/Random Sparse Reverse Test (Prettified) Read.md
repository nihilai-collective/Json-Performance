
----
### Random Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2777.54 | 0.0697595 | 6161.73ms | 676745 | 320 | 8.40786e+06 | 232362 | 0.142036 | 1.83902 | 8.31876 | 1.50224 | 0.00661215 | 0.000648167 | 6.76492e-06 | 1(Win) | true |
| simdjson (ondemand) | 2299.04 | 0.166898 | 7363.06ms | 676745 | 40 | 8.78051e+06 | 280724 | 0.00418246 | 2.2183 | 9.71284 | 1.59304 | 0.0078411 | 0.00142816 | 1.85077e-05 | 2(Loss) | true |
