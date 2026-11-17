
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3844.17 | 0.0298235 | 954.994ms | 9378 | 4890 | 2354.19 | 2326.52 | 0.0699806 | 1.3638 | 5.80657 | 0.975155 | 0.00118947 | 1.75104e-05 | 2.90023e-06 | 1(Win) | true |
| simdjson (ondemand) | 3835.58 | 0.021366 | 951.253ms | 9378 | 4890 | 1213.71 | 2331.74 | 0.0119571 | 1.36504 | 6.17936 | 0.920132 | 0.000757353 | 1.3956e-05 | 2.66036e-06 | 2(Loss) | true |
