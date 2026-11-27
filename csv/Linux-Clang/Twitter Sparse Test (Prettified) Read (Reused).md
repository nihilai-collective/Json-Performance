
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8341.83 | 0.0355826 | 4973.26ms | 360584 | 2560 | 550815 | 41223.5 | 0.181013 | 0.607295 | 2.87949 | 0.363416 | 0.000865047 | 1.73406e-05 | 1.48934e-05 | 1(Win) | true |
| simdjson (ondemand) | 7704.65 | 0.137199 | 5275.81ms | 360584 | 80 | 299984 | 44632.8 | 0.0828553 | 0.658765 | 3.13452 | 0.321631 | 0.000711242 | 3.11994e-06 | 2.32262e-06 | 2(Loss) | true |
