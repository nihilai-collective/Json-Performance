
----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2995.84 | 0.0735146 | 4712.04ms | 124597 | 160 | 136033 | 39663.3 | 0.0172359 | 1.7178 | 7.57047 | 1.38295 | 0.00465115 | 4.91585e-06 | 1.60518e-06 | 1(Win) | true |
| simdjson (ondemand) | 2494.65 | 0.0189607 | 5506.73ms | 124597 | 4890 | 398853 | 47631.9 | 0.174533 | 2.04637 | 8.31683 | 1.43036 | 0.00582442 | 6.23031e-06 | 2.10905e-06 | 2(Loss) | true |
