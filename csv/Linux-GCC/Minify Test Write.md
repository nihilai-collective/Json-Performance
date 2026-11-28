
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21970 | 0.491425 | 2153.9ms | 466906 | 160 | 1.58721e+06 | 20267.5 | 0.0482223 | 0.112527 | 1(Win) | true |
| simdjson (ondemand) | 18262.2 | 0.0460164 | 2531.25ms | 466906 | 30 | 3776.6 | 24382.4 | 0.86897 | 0.135416 | 2(Loss) | true |
| Glaze | 2755.12 | 0.241248 | 8374.7ms | 466906 | 640 | 9.72937e+07 | 161618 | 0.208743 | 0.898464 | 3(Loss) | true |
