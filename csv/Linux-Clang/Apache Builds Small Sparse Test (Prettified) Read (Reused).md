
----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4619.6 | 0.102288 | 784.859ms | 3370 | 320 | 162.051 | 695.706 | 0.016168 | 1.18049 | 4.94421 | 0.78457 | 0.00060089 | 6.30564e-05 | 1.29822e-05 | 1(Win) | true |
| simdjson (ondemand) | 3742.25 | 0.0626596 | 802.21ms | 3370 | 4890 | 1416.05 | 858.81 | 0.0814221 | 1.44008 | 5.6638 | 0.828784 | 0.0012094 | 3.11906e-05 | 4.06571e-06 | 2(Loss) | true |
