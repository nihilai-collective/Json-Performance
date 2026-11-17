
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2031.57 | 0.0275868 | 965.121ms | 4926 | 4890 | 1989.93 | 2312.4 | 0.0258993 | 2.57672 | 11.4367 | 2.14819 | 0.0053445 | 4.99416e-05 | 1.62736e-05 | 1(Win) | true |
| simdjson (ondemand) | 1662.04 | 0.0366563 | 1015.39ms | 4926 | 4890 | 5249.44 | 2826.53 | 0.0090203 | 3.1341 | 14.0081 | 2.29882 | 0.00483321 | 5.58781e-05 | 2.68597e-05 | 2(Loss) | true |
