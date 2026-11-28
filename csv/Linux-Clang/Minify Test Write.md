
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 23213.8 | 0.208681 | 1915.62ms | 466906 | 640 | 1.02545e+06 | 19181.5 | 0.320373 | 0.106476 | 1(Win) | true |
| Jsonifier | 22654.8 | 0.0975336 | 1982.65ms | 466906 | 4890 | 1.79703e+06 | 19654.8 | 0.0229743 | 0.109128 | 2(Loss) | true |
| Glaze | 2827.86 | 0.0970932 | 8218.29ms | 466906 | 2560 | 5.98359e+07 | 157461 | 0.528516 | 0.875352 | 3(Loss) | true |
