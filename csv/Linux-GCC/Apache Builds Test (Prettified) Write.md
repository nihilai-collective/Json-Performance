
----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23688.2 | 0.127051 | 1285.13ms | 136037 | 30 | 1452.53 | 5476.77 | 0.138351 | 0.219161 | 0.86847 | 0.125694 | 7.17942e-05 | 4.90063e-06 | 3.43044e-06 | 1(Win) | true |
| Glaze | 7289.94 | 0.0540341 | 2528.64ms | 136076 | 2560 | 236859 | 17801.5 | 0.178139 | 0.698165 | 3.79973 | 0.638342 | 0.000113413 | 1.80764e-05 | 1.58919e-05 | 2(Loss) | true |
| simdjson (reflection) | 636.887 | 0.133047 | 5367.72ms | 136037 | 640 | 4.70089e+07 | 203702 | 0.0571742 | 7.90545 | 34.719 | 7.11326 | 0.0266514 | 0.0108771 | 0.000275798 | 3(Loss) | true |
