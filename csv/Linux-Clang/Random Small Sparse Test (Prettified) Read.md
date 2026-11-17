
----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3656.7 | 0.0422331 | 928.68ms | 8150 | 1280 | 1031.46 | 2125.53 | 0.229854 | 1.44663 | 6.02994 | 1.04245 | 0.00167418 | 9.87347e-06 | 8.6273e-07 | 1(Win) | true |
| simdjson (ondemand) | 3437.55 | 0.0349148 | 946.175ms | 8150 | 4890 | 3047.51 | 2261.04 | 0.209004 | 1.52307 | 6.57546 | 0.982332 | 0.000950883 | 1.66359e-05 | 3.28704e-06 | 2(Loss) | true |
