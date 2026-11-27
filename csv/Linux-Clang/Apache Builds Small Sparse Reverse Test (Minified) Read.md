
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2334.52 | 0.0933876 | 828.348ms | 2632 | 4890 | 4930.2 | 1075.2 | 0.0280064 | 2.28783 | 9.1117 | 1.731 | 0.00254761 | 5.99822e-05 | 3.10789e-05 | 1(Win) | true |
| simdjson (ondemand) | 2011.08 | 0.046418 | 847.684ms | 2632 | 4890 | 1641.32 | 1248.12 | 0.478169 | 2.62797 | 10.1364 | 1.71315 | 0.00408951 | 2.74271e-05 | 9.09057e-06 | 2(Loss) | true |
