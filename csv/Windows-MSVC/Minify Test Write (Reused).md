
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24462.4 | 0.0637027 | 1780.31ms | 466906 | 40 | 5378.21 | 18202.5 | 0.4058 | 0.101106 | 1(Win) | true |
| simdjson (ondemand) | 23228.4 | 0.234691 | 1981.55ms | 466906 | 1280 | 2.59074e+06 | 19169.5 | 0.22834 | 0.106435 | 2(Loss) | true |
| Glaze | 2126.26 | 0.146911 | 5513.01ms | 466906 | 320 | 3.0289e+07 | 209418 | 0.394773 | 1.16426 | 3(Loss) | true |
