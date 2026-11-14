
----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4704.81 | 0.096698 | 817.642ms | 4857 | 640 | 580.053 | 984.523 | 0.12063 | 1.13933 | 4.95882 | 0.756434 | 0.000621526 | 1.57633e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4070.63 | 0.0872462 | 833.52ms | 4857 | 320 | 315.396 | 1137.91 | 0.0379129 | 1.3107 | 5.4441 | 0.700432 | 0.00062796 | 1.15812e-05 | 1.2868e-06 | 2(Loss) | true |
