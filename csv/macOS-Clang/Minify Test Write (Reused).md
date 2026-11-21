
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2133.61 | 0.509544 | 5586.45ms | 466906 | 160 | 1.8093e+08 | 208696 | 0.0521635 | 1(Win) | true |
| Glaze | 1537.06 | 0.374115 | 7533.67ms | 466906 | 640 | 7.51736e+08 | 289693 | 0.745414 | 2(Loss) | true |
| simdjson (ondemand) | 1132.81 | 2.91079 | 5167.2ms | 466906 | 30 | 3.92725e+09 | 393072 | 1.04444 | 3(Loss) | true |
