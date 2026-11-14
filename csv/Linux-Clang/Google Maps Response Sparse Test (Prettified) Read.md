
----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4165.3 | 0.0407278 | 1302.04ms | 25388 | 1280 | 7173.94 | 5812.76 | 0.0544358 | 1.24486 | 5.71057 | 0.959627 | 0.00205363 | 1.03088e-05 | 2.80029e-06 | 1(Win) | true |
| simdjson (ondemand) | 3827.38 | 0.0417091 | 1349.29ms | 25388 | 160 | 1113.87 | 6325.98 | 0.0294334 | 1.35478 | 6.08165 | 0.903695 | 0.00226165 | 7.87774e-06 | 4.92359e-07 | 2(Loss) | true |
