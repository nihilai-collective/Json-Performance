
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7764.79 | 0.463773 | 6161.7ms | 466906 | 320 | 2.2634e+07 | 57345.6 | 0.251741 | 1(Win) | true |
| simdjson (ondemand) | 7598.78 | 0.303451 | 6426.27ms | 466906 | 80 | 2.52952e+06 | 58598.4 | 0.919814 | 2(Loss) | true |
| Glaze | 1620.53 | 0.453049 | 7036.72ms | 466906 | 320 | 4.95887e+08 | 274771 | 0.510948 | 3(Loss) | true |
