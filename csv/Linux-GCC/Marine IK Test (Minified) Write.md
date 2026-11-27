
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1347.56 | 0.0609573 | 8636.46ms | 1922245 | 80 | 5.50128e+07 | 1.36038e+06 | 0.0731428 | 3.75451 | 13.1326 | 0.653489 | 0.00226568 | 0.0595354 | 6.76358e-05 | 1(Win) | true |
| simdjson (reflection) | 1342.28 | 0.153714 | 8687.49ms | 1922245 | 40 | 1.76287e+08 | 1.36573e+06 | 0.654474 | 3.79407 | 13.6344 | 1.13441 | 0.00918196 | 0.0529228 | 6.77073e-05 | 2(Loss) | true |
| Glaze | 952.2 | 0.255325 | 5697.74ms | 1833577 | 160 | 3.51761e+09 | 1.83642e+06 | 0.862976 | 5.27836 | 16.0436 | 1.0529 | 0.0010049 | 0.0768802 | 0.000113797 | 3(Loss) | true |
