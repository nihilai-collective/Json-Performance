
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3848.43 | 0.0402097 | 878.53ms | 6701 | 4890 | 2180.13 | 1660.57 | 0.188834 | 1.38353 | 6.08685 | 1.01224 | 0.00037906 | 1.45875e-05 | 2.19727e-06 | 1(Win) | true |
| simdjson (ondemand) | 3010.91 | 0.139574 | 945.372ms | 6701 | 160 | 1404.15 | 2122.47 | 0.183998 | 1.77563 | 8.03701 | 1.20415 | 0.000935495 | 2.42501e-05 | 0 | 2(Loss) | true |
