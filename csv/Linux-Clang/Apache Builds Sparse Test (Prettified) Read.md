
----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2903.32 | 0.035618 | 4828.3ms | 124597 | 2560 | 544007 | 40927.2 | 0.140547 | 1.74533 | 7.51946 | 1.34881 | 0.00490452 | 1.8657e-05 | 1.3876e-05 | 1(Win) | true |
| simdjson (ondemand) | 2472.65 | 0.0221372 | 5567.05ms | 124597 | 4890 | 553406 | 48055.8 | 0.092778 | 2.06316 | 8.3181 | 1.42913 | 0.00599008 | 1.09588e-05 | 7.60407e-06 | 2(Loss) | true |
