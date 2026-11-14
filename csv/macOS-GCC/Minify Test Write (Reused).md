
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2109.57 | 0.388085 | 5364.85ms | 466906 | 640 | 4.29443e+08 | 211074 | 0.500899 | 1(Win) | true |
| Glaze | 1303.03 | 0.854451 | 8147.62ms | 466906 | 80 | 6.82052e+08 | 341725 | 0.320166 | 2(Loss) | true |
| simdjson (ondemand) | 999.952 | 0.365303 | 5786.05ms | 466906 | 640 | 1.6935e+09 | 445298 | 2.03138 | 3(Loss) | true |
