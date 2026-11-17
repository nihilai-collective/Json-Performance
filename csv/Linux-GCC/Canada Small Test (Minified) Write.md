
----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1974.43 | 0.0878698 | 958.179ms | 4630 | 320 | 1235.69 | 2236.35 | 0.120598 | 2.60838 | 7.81598 | 0.410583 | 0.000215983 | 2.63229e-05 | 2.02484e-06 | 1(Win) | true |
| Glaze | 1562.87 | 0.0565129 | 1009.76ms | 4630 | 2560 | 6526.07 | 2825.26 | 0.063364 | 3.2794 | 9.99309 | 0.717495 | 0.000371895 | 4.43777e-05 | 1.03773e-05 | 2(Loss) | true |
| simdjson (reflection) | 1067.26 | 0.0217767 | 1143.55ms | 4630 | 160 | 129.874 | 4137.23 | 0.0138963 | 4.79108 | 15.3685 | 1.44384 | 0.000647948 | 2.15983e-05 | 8.09935e-06 | 3(Loss) | true |
