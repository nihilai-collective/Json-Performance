
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7623.76 | 0.171602 | 6431.52ms | 466906 | 320 | 3.21451e+06 | 58406.4 | 0.10399 | 1(Win) | true |
| Jsonifier | 6474.78 | 0.245503 | 6632.62ms | 466906 | 2560 | 7.2973e+07 | 68770.9 | 3.94562 | 2(Loss) | true |
| Glaze | 1286.72 | 0.554987 | 7596.26ms | 466906 | 40 | 1.47542e+08 | 346054 | 0.969151 | 3(Loss) | true |
