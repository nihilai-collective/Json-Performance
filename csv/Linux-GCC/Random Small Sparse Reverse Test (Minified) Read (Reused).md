
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2232.53 | 0.0577057 | 938.233ms | 4926 | 2560 | 3774.6 | 2104.25 | 0.025704 | 2.34813 | 10.7605 | 2.01583 | 0.00354885 | 2.80717e-05 | 1.31636e-05 | 1(Win) | true |
| simdjson (ondemand) | 1559.08 | 0.0289826 | 1032.95ms | 4926 | 320 | 244.05 | 3013.19 | 0.00933308 | 3.34852 | 13.4015 | 2.35323 | 0.00727771 | 5.7095e-06 | 6.34389e-07 | 2(Loss) | true |
