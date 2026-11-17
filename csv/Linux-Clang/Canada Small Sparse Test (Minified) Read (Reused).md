
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7678.7 | 0.0779527 | 769.879ms | 4630 | 2560 | 514.386 | 575.034 | 0.0942408 | 0.718273 | 3.59698 | 0.461987 | 0.000432556 | 1.82235e-05 | 4.80899e-06 | 1(Win) | true |
| simdjson (ondemand) | 6751.57 | 0.0560572 | 774.604ms | 4630 | 4890 | 657.24 | 653.998 | 0.0263162 | 0.808052 | 4.06501 | 0.483586 | 0.000432628 | 1.16162e-05 | 2.65009e-06 | 2(Loss) | true |
