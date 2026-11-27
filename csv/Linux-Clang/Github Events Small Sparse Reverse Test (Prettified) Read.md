
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3932.69 | 0.123768 | 770.691ms | 2158 | 4890 | 2051.41 | 523.313 | 0.217951 | 1.40076 | 5.63531 | 0.980538 | 0.00108599 | 5.43941e-05 | 1.83841e-05 | 1(Win) | true |
| simdjson (ondemand) | 3200.96 | 0.0795647 | 784.887ms | 2158 | 640 | 167.48 | 642.941 | 0.0369533 | 1.71142 | 7.04356 | 1.13531 | 0.000619063 | 1.59291e-05 | 2.8962e-06 | 2(Loss) | true |
