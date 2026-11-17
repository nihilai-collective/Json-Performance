
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4144.31 | 0.0352662 | 8595.99ms | 699405 | 2560 | 8.24728e+06 | 160945 | 0.0920891 | 1.21125 | 4.79602 | 1.19835 | 0.00190331 | 0.000292565 | 8.06601e-06 | 1(Win) | true |
| Glaze | 3170.93 | 0.192153 | 5550.71ms | 699405 | 640 | 1.04558e+08 | 210350 | 0.0403503 | 1.58671 | 6.2876 | 1.35582 | 0.00202751 | 0.00107157 | 1.48743e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2441.4 | 0.100493 | 7858.44ms | 767297 | 1280 | 1.16127e+08 | 299726 | 0.0627442 | 2.05234 | 8.04353 | 1.07977 | 0.00360769 | 0.0968921 | 1.84566e-05 | 3(Loss) | true |
