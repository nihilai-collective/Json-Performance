
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3340.54 | 0.0879858 | 865.017ms | 4857 | 320 | 476.297 | 1386.6 | 0.17429 | 1.58611 | 6.96644 | 1.19518 | 0.00146374 | 1.22246e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 2390.36 | 0.134629 | 910.893ms | 4857 | 320 | 2177.87 | 1937.78 | 0.160072 | 2.20728 | 10.1316 | 1.53799 | 0.00178673 | 8.36422e-06 | 0 | 2(Loss) | true |
