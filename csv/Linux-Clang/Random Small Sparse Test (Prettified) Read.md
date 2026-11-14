
----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3667.29 | 0.0403829 | 927.241ms | 8150 | 1280 | 937.63 | 2119.4 | 0.00328081 | 1.43142 | 6.02994 | 1.04245 | 0.00168549 | 1.66794e-05 | 4.79294e-07 | 1(Win) | true |
| simdjson (ondemand) | 3375.32 | 0.0372441 | 945.99ms | 8150 | 4890 | 3596.75 | 2302.73 | 0.0262292 | 1.55172 | 6.56638 | 0.97951 | 0.00090652 | 2.06255e-05 | 3.03612e-06 | 2(Loss) | true |
