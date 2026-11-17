
----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3482.49 | 0.237787 | 3732.57ms | 108313 | 320 | 1.59187e+06 | 29661.4 | 0.0779447 | 1.46537 | 8.00572 | 1.39499 | 0.00124336 | 3.37563e-06 | 2.88516e-07 | 1(Win) | true |
| simdjson (ondemand) | 2658.99 | 0.169533 | 4642.57ms | 108313 | 160 | 693994 | 38847.6 | 0.0680524 | 1.93825 | 10.1619 | 1.54892 | 0.00272953 | 3.51989e-06 | 2.88516e-07 | 2(Loss) | true |
