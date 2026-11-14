
----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3242.98 | 0.0219109 | 1475.23ms | 25388 | 2560 | 6850.57 | 7465.93 | 0.000507511 | 1.59642 | 7.20372 | 1.28053 | 0.00293389 | 6.693e-06 | 1.24628e-06 | 1(Win) | true |
| simdjson (ondemand) | 3200.44 | 0.0186255 | 1483.43ms | 25388 | 4890 | 9708.72 | 7565.18 | 0.0759568 | 1.61747 | 7.34749 | 1.13329 | 0.00352359 | 7.69247e-06 | 1.61099e-06 | 2(Loss) | true |
