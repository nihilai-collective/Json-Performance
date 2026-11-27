
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4063.17 | 0.157259 | 7164.46ms | 1151920 | 40 | 7.23116e+06 | 270370 | 0.0751553 | 1.25332 | 6.07408 | 1.12477 | 0.00431375 | 0.0188824 | 3.31837e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 3678.74 | 0.0933105 | 7882.99ms | 1151920 | 160 | 1.2423e+07 | 298623 | 0.106286 | 1.38664 | 6.25494 | 0.981089 | 0.00616599 | 0.0559524 | 4.75076e-05 | 2(Loss) | true |
| simdjson (reflection) | 3048.52 | 0.0348732 | 9388.57ms | 1151920 | 640 | 1.01072e+07 | 360357 | 0.0558474 | 1.66072 | 6.74803 | 1.07317 | 0.00746618 | 0.0478817 | 7.00217e-05 | 3(Loss) | true |
| simdjson (ondemand) | 3010.27 | 0.0385355 | 9497.99ms | 1151920 | 640 | 1.26571e+07 | 364936 | 0.149291 | 1.67926 | 6.91583 | 1.09448 | 0.00721283 | 0.0490629 | 5.57995e-05 | 4(Loss) | true |
| Glaze | 2583.59 | 0.0371278 | 5508.31ms | 1151920 | 640 | 1.59506e+07 | 425206 | 0.174055 | 1.96172 | 8.47786 | 1.61279 | 0.00713728 | 0.0146642 | 5.96436e-05 | 5(Loss) | true |
