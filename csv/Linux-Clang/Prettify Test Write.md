
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4363.87 | 0.164678 | 8180.12ms | 699405 | 1280 | 8.1095e+07 | 152847 | 0.221317 | 1.14402 | 4.31682 | 0.737579 | 0.00441463 | 0.00304327 | 4.29606e-06 | 1(Win) | true |
| Glaze | 3902.7 | 0.0485541 | 9130.14ms | 699405 | 2560 | 1.76286e+07 | 170908 | 0.0346006 | 1.29627 | 5.22157 | 1.16245 | 0.00247909 | 0.00102303 | 1.15578e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2315.64 | 0.126037 | 8289.88ms | 767297 | 1280 | 2.03044e+08 | 316004 | 0.194466 | 2.15253 | 8.6478 | 1.18016 | 0.0030322 | 0.100398 | 8.55275e-06 | 3(Loss) | true |
