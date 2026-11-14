
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4985.28 | 0.146327 | 745.648ms | 1691 | 2560 | 573.586 | 323.485 | 0.11314 | 1.16129 | 4.22413 | 0.656417 | 0.000806891 | 3.74224e-05 | 6.00606e-06 | 1(Win) | true |
| simdjson (ondemand) | 4493.63 | 0.210053 | 743.803ms | 1691 | 1280 | 727.374 | 358.877 | 0.0612091 | 1.28819 | 4.75458 | 0.636902 | 0.0011795 | 7.29967e-05 | 2.31002e-05 | 2(Loss) | true |
