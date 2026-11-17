
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4158.09 | 0.149257 | 8616.55ms | 699405 | 160 | 9.17188e+06 | 160411 | 0.0782375 | 1.20637 | 4.79552 | 1.19825 | 0.00201301 | 0.000270534 | 4.13745e-06 | 1(Win) | true |
| Glaze | 3164.73 | 0.101944 | 5535.68ms | 699405 | 30 | 1.38493e+06 | 210762 | 0.0324801 | 1.59631 | 6.2869 | 1.35566 | 0.0019976 | 0.00108902 | 3.56493e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2472.82 | 0.186997 | 7765.7ms | 767297 | 320 | 9.79856e+07 | 295918 | 0.0196257 | 2.03245 | 8.04403 | 1.07991 | 0.00340006 | 0.0916605 | 8.18987e-05 | 3(Loss) | true |
