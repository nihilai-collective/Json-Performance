
----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2821.26 | 0.0440257 | 8446.77ms | 409725 | 2560 | 9.51812e+06 | 138500 | 0.0185586 | 1.81003 | 8.73548 | 1.60724 | 0.0044196 | 1.16618e-05 | 4.15294e-06 | 1(Win) | true |
| simdjson (ondemand) | 2134.69 | 0.0902919 | 5410.04ms | 409725 | 160 | 4.3705e+06 | 183045 | 0.00600228 | 2.38545 | 10.0685 | 1.57735 | 0.00775148 | 3.88675e-05 | 4.02709e-06 | 2(Loss) | true |
