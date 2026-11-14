
----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2074.3 | 0.0584949 | 5538.82ms | 409725 | 30 | 364249 | 188374 | 0.0759882 | 2.48249 | 11.8053 | 2.22781 | 0.00742238 | 3.57964e-06 | 5.69488e-07 | 1(Win) | true |
| simdjson (ondemand) | 1620.27 | 0.0764482 | 6887.38ms | 409725 | 160 | 5.43832e+06 | 241160 | 0.0449991 | 3.15811 | 14.3423 | 2.38762 | 0.0104375 | 2.54897e-05 | 6.71182e-06 | 2(Loss) | true |
