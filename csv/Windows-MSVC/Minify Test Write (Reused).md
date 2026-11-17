
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3496.17 | 0.370486 | 6566.38ms | 466906 | 80 | 1.78118e+07 | 127361 | 0.0697323 | 0.707964 | 1(Win) | true |
| Glaze | 1750.74 | 0.328126 | 6663.98ms | 466906 | 80 | 5.5717e+07 | 254336 | 0.474549 | 1.41399 | 2(Loss) | true |
| simdjson (ondemand) | 1319.94 | 0.213325 | 8671.79ms | 466906 | 80 | 4.14311e+07 | 337346 | 0.370051 | 1.87544 | 3(Loss) | true |
