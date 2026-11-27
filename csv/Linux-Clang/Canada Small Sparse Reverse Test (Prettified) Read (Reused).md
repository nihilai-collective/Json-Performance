
----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10299.3 | 0.0669445 | 828.815ms | 11579 | 2560 | 1318.85 | 1072.17 | 0.0352068 | 0.519113 | 2.68054 | 0.357112 | 0.000280141 | 6.30857e-06 | 1.72052e-06 | 1(Win) | true |
| simdjson (ondemand) | 8660.37 | 0.0503068 | 850.299ms | 11579 | 4890 | 2012.02 | 1275.07 | 0.0375818 | 0.612739 | 2.9481 | 0.359098 | 0.000259178 | 8.53036e-06 | 1.23628e-06 | 2(Loss) | true |
