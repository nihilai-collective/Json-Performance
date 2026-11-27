
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2095.11 | 0.0629224 | 5521.45ms | 409725 | 320 | 4.40688e+06 | 186503 | 0.302103 | 2.42901 | 11.5983 | 2.16044 | 0.00732722 | 1.3416e-05 | 5.71267e-06 | 1(Win) | true |
| simdjson (ondemand) | 1608.82 | 0.0670241 | 6901.67ms | 409725 | 320 | 8.47977e+06 | 242877 | 0.0340424 | 3.17798 | 14.2911 | 2.37458 | 0.0105099 | 7.42953e-05 | 1.39575e-05 | 2(Loss) | true |
