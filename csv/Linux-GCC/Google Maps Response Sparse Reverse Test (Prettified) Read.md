
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3396.59 | 0.119098 | 1441.41ms | 25388 | 40 | 2882.98 | 7128.3 | 0.0294514 | 1.52513 | 7.18391 | 1.27044 | 0.00378427 | 5.9083e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3247.46 | 0.0447165 | 1474.09ms | 25388 | 1280 | 14227.1 | 7455.63 | 0.0265982 | 1.59342 | 7.20195 | 1.16165 | 0.00321138 | 8.3701e-06 | 3.16956e-06 | 2(Loss) | true |
