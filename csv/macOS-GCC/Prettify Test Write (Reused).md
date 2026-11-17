
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3008.56 | 0.679222 | 5887.25ms | 699405 | 40 | 9.07035e+07 | 221702 | 1.17254 | 1(Win) | true |
| Glaze | 2145.01 | 0.171403 | 7845.53ms | 699405 | 1280 | 3.6362e+08 | 310957 | 0.282442 | 2(Loss) | true |
| simdjson (ondemand) | 1479.03 | 0.159848 | 6504.21ms | 767297 | 640 | 4.00281e+08 | 494751 | 0.685873 | 3(Loss) | true |
