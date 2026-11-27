
----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6397.08 | 0.102568 | 9461.33ms | 10018896 | 80 | 1.87754e+08 | 1.49361e+06 | 0.0675865 | 0.791397 | 2.60106 | 0.120868 | 0.00014427 | 0.0249624 | 0.00049996 | 1(Win) | true |
| Glaze | 3097.53 | 0.172093 | 9579.86ms | 9930228 | 160 | 4.42928e+09 | 3.05734e+06 | 0.0384076 | 1.62307 | 4.41437 | 0.474335 | 0.000700253 | 0.0757756 | 0.0103026 | 2(Loss) | true |
| simdjson (reflection) | 437.57 | 0.474413 | 6625.31ms | 10018896 | 30 | 3.21943e+11 | 2.1836e+07 | 2.26131 | 11.5364 | 35.8508 | 5.24904 | 0.0156111 | 0.314241 | 0.158582 | 3(Loss) | true |
