
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6166.01 | 0.0678566 | 769.52ms | 2821 | 640 | 56.1 | 436.314 | 0.107909 | 0.897948 | 3.55229 | 0.488834 | 0.000650811 | 2.60324e-05 | 2.76941e-06 | 1(Win) | true |
| simdjson (ondemand) | 5705.37 | 0.168761 | 767.203ms | 2821 | 320 | 202.644 | 471.541 | 0.22152 | 0.976106 | 3.92449 | 0.43318 | 0.000554989 | 1.44009e-05 | 1.10776e-06 | 2(Loss) | true |
