
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 24623.6 | 0.0978543 | 1817.63ms | 466906 | 2560 | 801598 | 18083.3 | 0.147216 | 0.100396 | 1(Win) | true |
| Jsonifier | 22638.5 | 0.169578 | 1986.15ms | 466906 | 1280 | 1.42401e+06 | 19669 | 0.183605 | 0.109213 | 2(Loss) | true |
| Glaze | 2786.72 | 0.103893 | 8135.46ms | 466906 | 2560 | 7.0548e+07 | 159785 | 0.211905 | 0.888285 | 3(Loss) | true |
