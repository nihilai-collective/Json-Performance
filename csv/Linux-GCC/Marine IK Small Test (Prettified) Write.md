
----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6461.03 | 0.136288 | 1091.49ms | 24579 | 1280 | 31293.4 | 3627.96 | 0.0621949 | 0.790555 | 1.88596 | 0.105497 | 6.30937e-05 | 2.00247e-05 | 9.24951e-06 | 1(Win) | true |
| Glaze | 3457.82 | 0.0707246 | 1415.45ms | 24579 | 4890 | 112402 | 6778.94 | 0.323455 | 1.47662 | 3.91025 | 0.475813 | 0.000347546 | 2.33378e-05 | 1.12238e-05 | 2(Loss) | true |
| simdjson (reflection) | 530.244 | 0.092585 | 5232.84ms | 24893 | 4890 | 8.40221e+06 | 44771.5 | 0.00556044 | 9.57697 | 36.8001 | 6.04387 | 0.00773168 | 0.000210644 | 0.000147396 | 3(Loss) | true |
