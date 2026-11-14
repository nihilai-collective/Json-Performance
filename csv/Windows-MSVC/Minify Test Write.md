
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2852.03 | 0.0434092 | 7979.27ms | 466906 | 1280 | 5.8793e+06 | 156126 | 0.0133624 | 1.06554 | 1(Win) | true |
| Glaze | 1824.51 | 0.135773 | 6261.15ms | 466906 | 80 | 8.78379e+06 | 244052 | 0.134013 | 1.6657 | 2(Loss) | true |
| simdjson (ondemand) | 1439.49 | 0.113924 | 7869.62ms | 466906 | 1280 | 1.5896e+08 | 309330 | 0.218919 | 2.11103 | 3(Loss) | true |
