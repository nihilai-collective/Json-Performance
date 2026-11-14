
----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3992.44 | 0.102818 | 9619.99ms | 676745 | 320 | 8.84026e+06 | 161654 | 0.0666296 | 1.26895 | 6.18355 | 0.976767 | 0.00281161 | 0.000849951 | 8.12714e-07 | 1(Win) | true |
| simdjson (ondemand) | 3340.78 | 0.0873202 | 5623.54ms | 676745 | 160 | 4.55306e+06 | 193187 | 0.0329842 | 1.53017 | 6.41319 | 0.974404 | 0.00386757 | 0.0025016 | 3.11232e-06 | 2(Loss) | true |
