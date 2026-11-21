
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1851.94 | 0.761095 | 5690.17ms | 466906 | 160 | 5.35798e+08 | 240437 | 2.5487 | 1(Win) | true |
| Glaze | 1440.52 | 0.970583 | 7630.97ms | 466906 | 80 | 7.2007e+08 | 309108 | 0.537526 | 2(Loss) | true |
| simdjson (ondemand) | 1199.95 | 0.469843 | 5003.39ms | 466906 | 30 | 9.11928e+07 | 371079 | 0.443971 | 3(Loss) | true |
