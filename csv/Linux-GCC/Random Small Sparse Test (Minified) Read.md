
----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2847.88 | 0.156884 | 886.646ms | 4926 | 40 | 267.892 | 1649.58 | 0.309724 | 1.81883 | 8.11206 | 1.45554 | 0.000553187 | 3.04507e-05 | 3.04507e-05 | 1(Win) | true |
| simdjson (ondemand) | 2186.16 | 0.0420117 | 949.099ms | 4926 | 320 | 260.803 | 2148.88 | 0.0762897 | 2.40043 | 9.94072 | 1.64251 | 0.00131636 | 1.71285e-05 | 1.26878e-06 | 2(Loss) | true |
