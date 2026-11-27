
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4700.11 | 0.113082 | 6988.84ms | 1151920 | 320 | 2.23544e+07 | 233730 | 0.229182 | 1.07618 | 5.58836 | 1.00638 | 0.00312953 | 0.0130369 | 1.32822e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 4216.11 | 0.0334907 | 7769.6ms | 1151920 | 640 | 4.87357e+06 | 260561 | 0.14747 | 1.20022 | 5.77047 | 0.863063 | 0.0049035 | 0.0478785 | 2.15293e-05 | 2(Loss) | true |
| simdjson (reflection) | 3571.92 | 0.0515026 | 8953.1ms | 1151920 | 320 | 8.02878e+06 | 307554 | 0.115374 | 1.41666 | 6.25085 | 0.951377 | 0.00486354 | 0.0372736 | 2.9874e-05 | 3(Loss) | true |
| simdjson (ondemand) | 3565.72 | 0.0449306 | 8927.59ms | 1151920 | 640 | 1.22635e+07 | 308088 | 0.00576015 | 1.43015 | 6.42358 | 0.973279 | 0.00442324 | 0.0370321 | 7.32134e-05 | 4(Loss) | true |
| Glaze | 2883.64 | 0.0510355 | 5405.53ms | 1151920 | 320 | 1.20964e+07 | 380962 | 0.210138 | 1.75912 | 7.99323 | 1.49521 | 0.00532454 | 0.00982514 | 2.18195e-05 | 5(Loss) | true |
