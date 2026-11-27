
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3297.69 | 0.0579573 | 1002.95ms | 9378 | 160 | 395.31 | 2712.07 | 0.0486489 | 1.58591 | 7.13713 | 1.25752 | 0.00159816 | 1.06633e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3242.45 | 0.146412 | 998.636ms | 9378 | 40 | 652.358 | 2758.28 | 0.0069483 | 1.58292 | 7.26679 | 1.11612 | 0.00198603 | 3.19898e-05 | 2.39923e-05 | 2(Loss) | true |
