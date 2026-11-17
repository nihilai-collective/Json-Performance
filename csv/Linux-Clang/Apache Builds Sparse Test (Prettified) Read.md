
----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2914.44 | 0.0249611 | 4813.29ms | 124597 | 2560 | 265139 | 40771.1 | 0.219594 | 1.74487 | 7.5808 | 1.38444 | 0.00535958 | 1.29355e-05 | 8.35193e-06 | 1(Win) | true |
| simdjson (ondemand) | 2358.04 | 0.0342765 | 5764.1ms | 124597 | 1280 | 381871 | 50391.5 | 0.0506046 | 2.14894 | 8.34947 | 1.4377 | 0.00969062 | 1.09854e-05 | 7.14178e-06 | 2(Loss) | true |
