
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4223.16 | 0.0428687 | 8448.08ms | 699405 | 2560 | 1.17356e+07 | 157940 | 0.193511 | 1.21044 | 4.75893 | 1.21772 | 0.00329968 | 0.000229677 | 9.86665e-06 | 1(Win) | true |
| Glaze | 3204.02 | 0.0316074 | 5486.63ms | 699405 | 1280 | 5.54187e+06 | 208178 | 0.531906 | 1.59784 | 6.28759 | 1.35582 | 0.0020429 | 0.000764864 | 1.61041e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2460.78 | 0.156993 | 7764.73ms | 767297 | 320 | 6.97423e+07 | 297366 | 0.320577 | 2.04952 | 8.02247 | 1.07878 | 0.00380306 | 0.101752 | 0.000122243 | 3(Loss) | true |
