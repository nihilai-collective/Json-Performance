
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4508.7 | 0.135731 | 5277.39ms | 466906 | 320 | 5.74992e+06 | 98759.2 | 0.122617 | 0.548912 | 1(Win) | true |
| Glaze | 2854.56 | 0.0766011 | 8218.61ms | 466906 | 640 | 9.13755e+06 | 155988 | 0.02445 | 0.867155 | 2(Loss) | true |
| simdjson (ondemand) | 1793.34 | 0.117792 | 6305.14ms | 466906 | 640 | 5.47457e+07 | 248295 | 0.479765 | 1.38028 | 3(Loss) | true |
