
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21412.2 | 0.0579887 | 2100.04ms | 466906 | 30 | 4362.6 | 20795.5 | 0.132255 | 0.11547 | 1(Win) | true |
| simdjson (ondemand) | 17682 | 0.430865 | 2575.91ms | 466906 | 160 | 1.88366e+06 | 25182.5 | 0.11676 | 0.139852 | 2(Loss) | true |
| Glaze | 2561.87 | 0.144864 | 8851.99ms | 466906 | 320 | 2.02868e+07 | 173809 | 0.646516 | 0.96624 | 3(Loss) | true |
