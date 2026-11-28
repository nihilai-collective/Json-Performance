
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7501.56 | 0.0752713 | 6140.19ms | 466906 | 4890 | 9.76166e+06 | 59357.8 | 0.0597469 | 1(Win) | true |
| Jsonifier | 6321.64 | 0.773157 | 6523.49ms | 466906 | 160 | 4.74521e+07 | 70436.8 | 0.389948 | 2(Loss) | true |
| Glaze | 1640.71 | 0.791717 | 6954.6ms | 466906 | 160 | 7.38676e+08 | 271392 | 0.988331 | 3(Loss) | true |
