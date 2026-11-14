
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6910.21 | 0.0929936 | 824.102ms | 7932 | 320 | 331.619 | 1094.69 | 0.0949708 | 0.786528 | 3.53253 | 0.430408 | 0.000678423 | 1.14252e-05 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 6855.05 | 0.0253091 | 824.569ms | 7932 | 1280 | 99.8405 | 1103.5 | 0.023287 | 0.778533 | 3.68835 | 0.398764 | 0.000632623 | 1.23117e-05 | 2.46234e-06 | 2(Loss) | true |
