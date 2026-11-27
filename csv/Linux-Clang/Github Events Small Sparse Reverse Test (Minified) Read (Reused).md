
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3586.59 | 0.105856 | 760.317ms | 1691 | 2560 | 579.96 | 449.637 | 0.0208458 | 1.56361 | 6.33117 | 1.1236 | 0.000593214 | 2.91063e-05 | 8.08508e-06 | 1(Win) | true |
| simdjson (ondemand) | 2678.35 | 0.0647366 | 783.447ms | 1691 | 4890 | 742.953 | 602.11 | 0.103305 | 2.04477 | 8.33885 | 1.36251 | 0.00116169 | 4.72851e-05 | 2.24937e-05 | 2(Loss) | true |
