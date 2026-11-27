
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10197.4 | 0.658357 | 4389.58ms | 466906 | 2560 | 2.11563e+08 | 43665.5 | 0.0605267 | 0.297603 | 1(Win) | true |
| simdjson (ondemand) | 8927.4 | 0.922809 | 5354.02ms | 466906 | 40 | 8.4741e+06 | 49877.5 | 0.774204 | 0.340221 | 2(Loss) | true |
| Glaze | 1907.49 | 0.0698657 | 6336.47ms | 466906 | 1280 | 3.40465e+07 | 233436 | 2.45306 | 1.59314 | 3(Loss) | true |
