
----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5107.08 | 0.107145 | 7900.34ms | 6661897 | 160 | 2.84257e+08 | 1.24401e+06 | 0.13589 | 0.981355 | 2.94094 | 0.261234 | 7.57254e-05 | 0.0279372 | 0.000230702 | 1(Win) | true |
| Glaze | 3952.2 | 0.083696 | 5062.68ms | 6661897 | 160 | 2.89632e+08 | 1.60753e+06 | 0.136605 | 1.28664 | 4.22891 | 0.468988 | 8.303e-05 | 0.0244543 | 0.000395246 | 2(Loss) | true |
