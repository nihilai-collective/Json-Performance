
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7941.83 | 0.0958949 | 6651.63ms | 2090234 | 320 | 1.85391e+07 | 251000 | 0.031071 | 0.636528 | 3.25154 | 0.398873 | 0.00267546 | 0.0509243 | 3.2293e-06 | 1(Win) | true |
| simdjson (ondemand) | 7078.54 | 0.0363 | 7431.8ms | 2090234 | 1280 | 1.3376e+07 | 281612 | 0.258339 | 0.715518 | 3.65784 | 0.418405 | 0.00254726 | 0.0499222 | 9.77388e-07 | 2(Loss) | true |
