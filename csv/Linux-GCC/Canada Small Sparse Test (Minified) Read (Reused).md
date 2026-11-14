
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7326.36 | 0.0619173 | 771.215ms | 4630 | 2560 | 356.493 | 602.689 | 0.214139 | 0.748735 | 3.53218 | 0.45594 | 0.000432387 | 2.10077e-05 | 6.83383e-06 | 1(Win) | true |
| simdjson (ondemand) | 6669.67 | 0.131629 | 775.285ms | 4630 | 1280 | 972.003 | 662.029 | 0.0216002 | 0.821282 | 4.07991 | 0.484665 | 0.000432809 | 1.02929e-05 | 2.19357e-06 | 2(Loss) | true |
