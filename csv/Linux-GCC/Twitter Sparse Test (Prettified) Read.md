
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7843.93 | 0.143209 | 5133.29ms | 360584 | 80 | 315337 | 43840.2 | 0.00761229 | 0.649281 | 3.1148 | 0.360948 | 0.00117708 | 4.67991e-06 | 4.09059e-06 | 1(Win) | true |
| simdjson (ondemand) | 7450.15 | 0.0176866 | 5347.73ms | 360584 | 4890 | 325896 | 46157.4 | 0.0290042 | 0.680784 | 3.32074 | 0.339695 | 0.000868668 | 7.54513e-06 | 4.69246e-06 | 2(Loss) | true |
