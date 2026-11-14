
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2292.3 | 0.15751 | 5000.57ms | 466906 | 80 | 7.48902e+06 | 194249 | 0.0472491 | 1(Win) | true |
| Glaze | 1743.79 | 0.0902597 | 6563.36ms | 466906 | 1280 | 6.79938e+07 | 255350 | 0.0813455 | 2(Loss) | true |
| simdjson (ondemand) | 1249.58 | 0.165249 | 9039.18ms | 466906 | 640 | 2.21917e+08 | 356341 | 0.367734 | 3(Loss) | true |
