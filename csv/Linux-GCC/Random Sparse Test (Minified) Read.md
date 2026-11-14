
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2429.93 | 0.0422089 | 8605.99ms | 409725 | 640 | 2.94839e+06 | 160804 | 0.0110161 | 2.08964 | 10.159 | 1.78364 | 0.00542289 | 0.00141061 | 3.90315e-05 | 1(Win) | true |
| simdjson (ondemand) | 1937.63 | 0.0436972 | 5359.09ms | 409725 | 640 | 4.96972e+06 | 201661 | 0.191886 | 2.64161 | 10.8106 | 1.83693 | 0.00728311 | 0.0025961 | 1.04338e-05 | 2(Loss) | true |
