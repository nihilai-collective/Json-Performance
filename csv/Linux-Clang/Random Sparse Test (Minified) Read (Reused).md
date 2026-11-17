
----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2816.04 | 0.0811515 | 8458.92ms | 409725 | 160 | 2.02872e+06 | 138757 | 0.072549 | 1.81563 | 8.74816 | 1.60981 | 0.00470174 | 0.000274147 | 2.91354e-06 | 1(Win) | true |
| simdjson (ondemand) | 2185.75 | 0.171822 | 5271.89ms | 409725 | 1280 | 1.20768e+08 | 178769 | 0.0930927 | 2.31782 | 10.076 | 1.57788 | 0.00757586 | 0.00237251 | 4.27993e-05 | 2(Loss) | true |
