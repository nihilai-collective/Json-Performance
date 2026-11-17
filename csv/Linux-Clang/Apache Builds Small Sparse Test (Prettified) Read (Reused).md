
----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4575 | 0.0761393 | 789.203ms | 3370 | 2560 | 732.378 | 702.488 | 0.21811 | 1.1879 | 4.94421 | 0.78457 | 0.000600658 | 5.55221e-05 | 2.02847e-05 | 1(Win) | true |
| simdjson (ondemand) | 3760.91 | 0.0472325 | 804.567ms | 3370 | 4890 | 796.646 | 854.55 | 0.213553 | 1.43333 | 5.6724 | 0.832048 | 0.000744631 | 5.00628e-05 | 1.34714e-05 | 2(Loss) | true |
