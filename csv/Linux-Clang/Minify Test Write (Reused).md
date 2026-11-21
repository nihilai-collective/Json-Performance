
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4470.03 | 0.251947 | 5267.36ms | 466906 | 160 | 1.0078e+07 | 99613.7 | 0.296424 | 0.553691 | 1(Win) | true |
| Glaze | 2773.07 | 0.412556 | 8180.06ms | 466906 | 40 | 1.75534e+07 | 160571 | 0.304998 | 0.892661 | 2(Loss) | true |
| simdjson (ondemand) | 1875.13 | 0.0501774 | 6083.83ms | 466906 | 1280 | 1.81729e+07 | 237464 | 0.0924455 | 1.32013 | 3(Loss) | true |
