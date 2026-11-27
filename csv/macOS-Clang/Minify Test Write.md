
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7598.87 | 0.0812469 | 5914.5ms | 466906 | 2560 | 5.80249e+06 | 58597.7 | 0.0989739 | 1(Win) | true |
| Jsonifier | 7335.92 | 0.0477272 | 6272.17ms | 466906 | 4890 | 4.10384e+06 | 60698.1 | 0.213188 | 2(Loss) | true |
| Glaze | 1745.29 | 0.124148 | 6624.74ms | 466906 | 160 | 1.60517e+07 | 255131 | 0.0188174 | 3(Loss) | true |
