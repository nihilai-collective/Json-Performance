
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5659.65 | 0.0999646 | 765.816ms | 2821 | 2560 | 578.043 | 475.35 | 0.144592 | 0.984674 | 3.64977 | 0.493442 | 0.000814898 | 3.35098e-05 | 7.06199e-06 | 1(Win) | true |
| simdjson (ondemand) | 5634.13 | 0.0900074 | 764.2ms | 2821 | 320 | 59.1097 | 477.503 | 0.0869656 | 0.988345 | 3.92095 | 0.432471 | 0.000538373 | 2.99096e-05 | 1.10776e-06 | 2(Loss) | true |
