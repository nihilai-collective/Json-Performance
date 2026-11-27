
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7597.15 | 0.0678677 | 5978.3ms | 466906 | 2560 | 4.05065e+06 | 58610.9 | 0.28513 | 1(Win) | true |
| Jsonifier | 7372.73 | 0.245084 | 6231.16ms | 466906 | 160 | 3.50552e+06 | 60395 | 0.149677 | 2(Loss) | true |
| Glaze | 1745.09 | 0.168283 | 6790.35ms | 466906 | 80 | 1.47501e+07 | 255160 | 0.255923 | 3(Loss) | true |
