
----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5984.63 | 0.104549 | 1613.92ms | 53331 | 30 | 2368.33 | 8498.5 | 0.0709426 | 0.865382 | 4.20603 | 0.675911 | 0.00155819 | 3.12514e-06 | 1.25005e-06 | 1(Win) | true |
| simdjson (ondemand) | 4355.49 | 0.0348088 | 1909.45ms | 53331 | 1280 | 21148.2 | 11677.3 | 0.00741902 | 1.18545 | 5.7422 | 0.912959 | 0.00207137 | 1.40485e-05 | 1.01225e-05 | 2(Loss) | true |
