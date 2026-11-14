
----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4462.68 | 0.219258 | 789.013ms | 3370 | 160 | 398.934 | 720.169 | 0.167215 | 1.21896 | 5.14421 | 0.74273 | 0.000795623 | 2.96736e-05 | 7.4184e-06 | 1(Win) | true |
| simdjson (ondemand) | 3595.5 | 0.0520749 | 805.867ms | 3370 | 4890 | 1059.52 | 893.863 | 0.0746636 | 1.49669 | 5.66202 | 0.866766 | 0.00059511 | 2.83386e-05 | 4.12639e-06 | 2(Loss) | true |
