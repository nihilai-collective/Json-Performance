
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3483.76 | 0.494845 | 9757.93ms | 699405 | 2560 | 2.29794e+09 | 191461 | 0.458653 | 0.872171 | 1(Win) | true |
| Glaze | 2519.13 | 0.720665 | 6724ms | 699405 | 320 | 1.16512e+09 | 264775 | 0.226447 | 1.20604 | 2(Loss) | true |
| simdjson (ondemand) | 1291.13 | 0.767211 | 7264.99ms | 767297 | 320 | 6.05017e+09 | 566753 | 0.317057 | 2.35281 | 3(Loss) | true |
