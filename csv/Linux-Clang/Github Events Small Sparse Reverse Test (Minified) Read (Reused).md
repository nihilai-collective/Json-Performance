
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3440.28 | 0.054549 | 759.805ms | 1691 | 2560 | 167.384 | 468.76 | 0.203 | 1.62659 | 6.51391 | 1.13779 | 0.00127305 | 3.04923e-05 | 1.84802e-06 | 1(Win) | true |
| simdjson (ondemand) | 2633.5 | 0.0548655 | 772.96ms | 1691 | 4890 | 551.985 | 612.364 | 0.278055 | 2.08247 | 8.31461 | 1.35364 | 0.00258387 | 3.51917e-05 | 2.90241e-06 | 2(Loss) | true |
