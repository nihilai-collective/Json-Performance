
----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7194.57 | 0.0372909 | 4294.99ms | 264040 | 4890 | 833000 | 34999.8 | 0.0791991 | 0.701984 | 3.38811 | 0.457889 | 0.00119552 | 2.03384e-06 | 8.17872e-07 | 1(Win) | true |
| simdjson (ondemand) | 6195.73 | 0.0364567 | 4858.42ms | 264040 | 2560 | 562015 | 40642.2 | 0.0935373 | 0.817014 | 3.80213 | 0.416867 | 0.00144015 | 6.53162e-06 | 4.11869e-06 | 2(Loss) | true |
