
----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2377.4 | 0.0476898 | 4522.61ms | 94653 | 1280 | 419686 | 37969.2 | 0.0392454 | 2.12966 | 9.36435 | 1.7535 | 0.00584047 | 1.03338e-05 | 5.62911e-06 | 1(Win) | true |
| simdjson (ondemand) | 1799.96 | 0.0525478 | 5578.38ms | 94653 | 640 | 444461 | 50150.2 | 0.0429458 | 2.81802 | 10.9775 | 1.9397 | 0.0110882 | 3.94698e-05 | 3.14801e-05 | 2(Loss) | true |
