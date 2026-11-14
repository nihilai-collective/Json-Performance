
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.11 | 0.0449095 | 950.931ms | 4390 | 4890 | 5275.99 | 2312.91 | 0.0994556 | 2.892 | 13.7934 | 2.57517 | 0.00365965 | 3.97352e-05 | 8.19859e-06 | 1(Win) | true |
| simdjson (ondemand) | 1651.21 | 0.025639 | 972.835ms | 4390 | 4890 | 2066.51 | 2535.5 | 0.015554 | 3.16684 | 14.3973 | 2.35216 | 0.00330427 | 3.72663e-05 | 7.6396e-06 | 2(Loss) | true |
