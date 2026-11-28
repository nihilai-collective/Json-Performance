
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25132 | 0.0490361 | 1833.99ms | 466906 | 40 | 3019.23 | 17717.5 | 0.0329133 | 0.0983368 | 1(Win) | true |
| simdjson (ondemand) | 22924.4 | 0.156988 | 1980.64ms | 466906 | 2560 | 2.38034e+06 | 19423.7 | 0.0106598 | 0.107855 | 2(Loss) | true |
| Glaze | 2064.55 | 0.23133 | 5645.75ms | 466906 | 80 | 1.99142e+07 | 215678 | 0.024336 | 1.19911 | 3(Loss) | true |
