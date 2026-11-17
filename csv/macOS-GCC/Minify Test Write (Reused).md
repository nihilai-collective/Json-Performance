
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2464.34 | 0.123654 | 5011.06ms | 466906 | 640 | 3.19489e+07 | 180688 | 5.40965 | -(Win) | false |
| Glaze | 1513.61 | 0.329097 | 7582.96ms | 466906 | 640 | 5.99869e+08 | 294181 | 0.700224 | 2(Loss) | true |
| simdjson (ondemand) | 1100.72 | 0.650029 | 5392.74ms | 466906 | 320 | 2.2127e+09 | 404533 | 2.14691 | 3(Loss) | true |
