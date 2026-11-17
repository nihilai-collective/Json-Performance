
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25985.2 | 0.0723391 | 1517.64ms | 213963 | 30 | 968.041 | 7852.6 | 0.0381893 | 0.195786 | 0.625482 | 0.146194 | 7.5714e-05 | 9.34741e-07 | 1.5579e-07 | 1(Win) | true |
| Glaze | 5389.97 | 0.0790971 | 4536.63ms | 213963 | 2560 | 2.29544e+06 | 37857.6 | 0.0188696 | 0.932433 | 3.5942 | 0.575291 | 0.000546055 | 2.06118e-05 | 1.36195e-05 | 2(Loss) | true |
| simdjson (reflection) | 463.755 | 0.362792 | 5661.41ms | 213963 | 320 | 8.1539e+08 | 439997 | 0.273089 | 10.7536 | 41.6914 | 8.45658 | 0.0396713 | 0.21227 | 0.000475199 | 3(Loss) | true |
