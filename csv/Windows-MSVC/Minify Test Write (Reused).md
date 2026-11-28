
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22874.6 | 0.174893 | 1966ms | 466906 | 2560 | 2.96714e+06 | 19465.9 | 0.078725 | 0.108066 | 1(Win) | true |
| simdjson (ondemand) | 21487.6 | 0.058563 | 2124.86ms | 466906 | 40 | 5891.03 | 20722.5 | 0.0603573 | 0.114962 | 2(Loss) | true |
| Glaze | 1954.68 | 0.125562 | 5968.25ms | 466906 | 640 | 5.23603e+07 | 227800 | 0.625388 | 1.26643 | 3(Loss) | true |
