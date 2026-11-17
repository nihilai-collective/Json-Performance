
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2804.4 | 0.315625 | 6048.88ms | 699405 | 1280 | 7.21326e+08 | 237842 | 1.88152 | 1(Win) | true |
| Glaze | 2175.98 | 0.197656 | 7797.74ms | 699405 | 640 | 2.34935e+08 | 306531 | 0.308962 | 2(Loss) | true |
| simdjson (ondemand) | 1392.92 | 0.583587 | 6560.12ms | 767297 | 80 | 7.51931e+08 | 525338 | 0.103445 | 3(Loss) | true |
