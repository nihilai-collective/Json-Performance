
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3573.5 | 0.132745 | 8110.16ms | 1151920 | 320 | 5.329e+07 | 307417 | 0.0969349 | 1.4041 | 6.18085 | 0.947784 | 0.00589799 | 0.056016 | 0.000103791 | 1(Win) | true |
| Jsonifier | 3420.22 | 0.0808681 | 8610.73ms | 1151920 | 30 | 2.02401e+06 | 321194 | 0.205917 | 1.47663 | 6.67157 | 1.38546 | 0.00461872 | 0.0181101 | 0.000117659 | 2(Loss) | true |
| simdjson (ondemand) | 3024.3 | 0.0479973 | 9651.95ms | 1151920 | 320 | 9.727e+06 | 363244 | 0.25512 | 1.67039 | 6.95889 | 1.0905 | 0.00714583 | 0.0508411 | 0.000223203 | 3(Loss) | true |
| simdjson (reflection) | 2951.32 | 0.0423764 | 9855.29ms | 1151920 | 320 | 7.96177e+06 | 372225 | 0.0322237 | 1.71073 | 6.95213 | 1.09603 | 0.00754989 | 0.0435454 | 8.1101e-05 | 4(Loss) | true |
| Glaze | 2595.62 | 0.547432 | 5515.73ms | 1151920 | 160 | 8.58903e+08 | 423235 | 0.0902809 | 1.94598 | 8.47791 | 1.61298 | 0.00756687 | 0.0136403 | 6.00356e-05 | 5(Loss) | true |
