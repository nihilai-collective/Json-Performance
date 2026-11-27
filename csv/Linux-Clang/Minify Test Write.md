
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11203.1 | 0.160572 | 4736.6ms | 466906 | 2560 | 1.04271e+07 | 39745.9 | 0.0582092 | 0.453082 | 1.82619 | 0.103014 | 0.000483718 | 2.76647e-05 | 5.98438e-06 | 1(Win) | true |
| simdjson (ondemand) | 9168.31 | 0.0383934 | 5623.37ms | 466906 | 4890 | 1.70021e+06 | 48566.9 | 0.016428 | 0.551962 | 2.12712 | 0.0439747 | 6.98805e-05 | 0.000387466 | 1.79268e-06 | 2(Loss) | true |
| Glaze | 2608.61 | 0.0364022 | 9066.44ms | 466906 | 2560 | 9.88405e+06 | 170695 | 0.0536954 | 1.91916 | 7.74721 | 1.47693 | 0.0025239 | 0.000615179 | 2.06646e-06 | 3(Loss) | true |
