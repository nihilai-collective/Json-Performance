
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3088.5 | 0.275645 | 5792.52ms | 699405 | 80 | 2.83499e+07 | 215964 | 0.131561 | 0.801505 | 1(Win) | true |
| Jsonifier | 2645.54 | 0.280711 | 6757.38ms | 699405 | 640 | 3.20575e+08 | 252124 | 0.0867494 | 0.935445 | 2(Loss) | true |
| simdjson (ondemand) | 1580.71 | 0.648361 | 5909.42ms | 767297 | 40 | 3.60342e+08 | 462925 | 0.419825 | 1.56602 | 3(Loss) | true |
