
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24811.7 | 0.821658 | 1872.86ms | 466906 | 80 | 1.73948e+06 | 17946.2 | 0.651991 | 0.0995658 | 1(Win) | true |
| simdjson (ondemand) | 22794.3 | 0.467866 | 1968.7ms | 466906 | 1280 | 1.0692e+07 | 19534.5 | 0.0495671 | 0.108447 | 2(Loss) | true |
| Glaze | 2002.4 | 0.280714 | 5571.79ms | 466906 | 80 | 3.11727e+07 | 222371 | 0.31748 | 1.23624 | 3(Loss) | true |
