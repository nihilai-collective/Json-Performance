
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4588.63 | 0.358422 | 5283.27ms | 466906 | 80 | 9.67768e+06 | 97039 | 0.0588899 | 0.539343 | 1(Win) | true |
| Glaze | 2829.96 | 0.116109 | 8058.5ms | 466906 | 2560 | 8.54421e+07 | 157344 | 0.102296 | 0.8747 | 2(Loss) | true |
| simdjson (ondemand) | 1910.7 | 0.136155 | 5979.61ms | 466906 | 320 | 3.22173e+07 | 233043 | 0.0742644 | 1.29558 | 3(Loss) | true |
