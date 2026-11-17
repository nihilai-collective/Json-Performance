
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3182.99 | 0.0168891 | 7160.75ms | 466906 | 2560 | 1.42903e+06 | 139893 | 0.0962881 | 0.954687 | 1(Win) | true |
| Glaze | 1780.25 | 0.135485 | 6458.68ms | 466906 | 30 | 3.4451e+06 | 250120 | 0.0546106 | 1.70713 | 2(Loss) | true |
| simdjson (ondemand) | 1453.87 | 0.178245 | 7860.07ms | 466906 | 160 | 4.76831e+07 | 306271 | 0.00306111 | 2.09017 | 3(Loss) | true |
