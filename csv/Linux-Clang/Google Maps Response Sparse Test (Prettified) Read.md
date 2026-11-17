
----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4107.27 | 0.0659763 | 1313.74ms | 25388 | 320 | 4840.34 | 5894.88 | 0.0599926 | 1.26222 | 5.71057 | 0.959627 | 0.00205831 | 6.40066e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3985.73 | 0.0220398 | 1334.27ms | 25388 | 2560 | 4588.76 | 6074.65 | 0.0636759 | 1.30063 | 6.08343 | 0.904601 | 0.00173107 | 1.05549e-05 | 3.06186e-06 | 2(Loss) | true |
