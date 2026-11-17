
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3240.9 | 0.0480562 | 1000.41ms | 9378 | 2560 | 4502.23 | 2759.59 | 0.0181012 | 1.61004 | 7.2186 | 1.27661 | 0.00173749 | 1.74527e-05 | 1.66613e-06 | 1(Win) | true |
| simdjson (ondemand) | 3196.53 | 0.091136 | 1002.09ms | 9378 | 30 | 195.059 | 2797.9 | 0.00119138 | 1.63997 | 7.36458 | 1.13105 | 0.00131869 | 1.06633e-05 | 0 | 2(Loss) | true |
