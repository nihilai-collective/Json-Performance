
----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3098.39 | 0.0582123 | 4563.2ms | 124597 | 1280 | 637945 | 38350.6 | 0.0280251 | 1.64853 | 7.69258 | 1.31784 | 0.00448246 | 3.36084e-06 | 6.64643e-07 | 1(Win) | true |
| simdjson (ondemand) | 2455 | 0.018324 | 5587.15ms | 124597 | 4890 | 384648 | 48401.2 | 0.110618 | 2.08503 | 8.16149 | 1.4543 | 0.00568556 | 3.18737e-06 | 7.94381e-07 | 2(Loss) | true |
