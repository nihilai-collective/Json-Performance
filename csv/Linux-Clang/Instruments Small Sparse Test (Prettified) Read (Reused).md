
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6498.49 | 0.0884509 | 845.756ms | 7932 | 4890 | 5183.87 | 1164.05 | 0.0684989 | 0.805156 | 3.65419 | 0.395739 | 0.000808199 | 2.82308e-05 | 1.66291e-05 | 1(Win) | true |
| Jsonifier (generic) | 6419.17 | 0.0474292 | 847.265ms | 7932 | 160 | 49.9827 | 1178.43 | 0.024921 | 0.814602 | 3.49609 | 0.447428 | 0.000636662 | 6.30358e-06 | 0 | 2(Loss) | true |
