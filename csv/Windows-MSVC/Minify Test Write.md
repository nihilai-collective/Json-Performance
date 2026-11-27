
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9869.39 | 1.46077 | 4405.74ms | 466906 | 1280 | 5.5597e+08 | 45116.9 | 0.258725 | 0.307767 | 1(Win) | true |
| simdjson (ondemand) | 8467.79 | 1.47948 | 5394.12ms | 466906 | 320 | 1.93682e+08 | 52584.7 | 0.046926 | 0.35872 | 2(Loss) | true |
| Glaze | 1894.86 | 0.202841 | 6051.18ms | 466906 | 640 | 1.4541e+08 | 234991 | 0.388196 | 1.60385 | 3(Loss) | true |
