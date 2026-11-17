
----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3053.87 | 0.0994294 | 4637.3ms | 124597 | 80 | 119738 | 38909.6 | 0.0616874 | 1.6869 | 7.69259 | 1.31784 | 0.00474179 | 1.3042e-05 | 1.09353e-05 | 1(Win) | true |
| simdjson (ondemand) | 2438.65 | 0.0208662 | 5629.92ms | 124597 | 4890 | 505486 | 48725.7 | 0.0255628 | 2.09119 | 8.16262 | 1.45471 | 0.00538409 | 1.26067e-05 | 8.89576e-06 | 2(Loss) | true |
