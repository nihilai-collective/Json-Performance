
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2900.42 | 0.152584 | 825.978ms | 3370 | 640 | 1829.53 | 1108.08 | 0.0394673 | 1.83665 | 7.74807 | 1.39229 | 0.00059579 | 1.02003e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2698.46 | 0.0311727 | 832.024ms | 3370 | 640 | 88.2175 | 1191 | 0.128602 | 1.97355 | 7.83887 | 1.34955 | 0.00105527 | 1.57641e-05 | 1.8546e-06 | 2(Loss) | true |
