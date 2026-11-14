
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 339.659 | 0.170776 | 1257.65ms | 1811 | 160 | 12064.9 | 5084.82 | 0.0289995 | 15.2927 | 64.0276 | 11.3992 | 0.0175421 | 0.000176008 | 6.55715e-05 | 1(Win) | true |
| Glaze | 305.168 | 0.14546 | 1303.96ms | 1798 | 2560 | 171012 | 5618.89 | 0.0706102 | 16.6504 | 71.2742 | 12.1413 | 0.0206886 | 0.000229856 | 0.000122966 | 2(Loss) | true |
