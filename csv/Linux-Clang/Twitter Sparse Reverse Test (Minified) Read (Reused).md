
----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5109.11 | 0.0853916 | 5727.28ms | 264040 | 4890 | 8.66142e+06 | 49286.1 | 0.0767114 | 0.996665 | 5.23537 | 0.846243 | 0.00129128 | 3.92362e-06 | 1.67757e-06 | 1(Win) | true |
| simdjson (ondemand) | 3947.82 | 0.0236048 | 7179.28ms | 264040 | 4890 | 1.1085e+06 | 63784.1 | 0.0322437 | 1.27981 | 6.29934 | 0.919136 | 0.00268416 | 1.06401e-05 | 7.30896e-06 | 2(Loss) | true |
