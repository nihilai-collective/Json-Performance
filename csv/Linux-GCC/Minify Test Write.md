
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21170.6 | 0.0764264 | 2114.72ms | 466906 | 4890 | 1.26354e+06 | 21032.8 | 0.125934 | 0.116798 | 1(Win) | true |
| simdjson (ondemand) | 15883.2 | 0.1117 | 2796.72ms | 466906 | 1280 | 1.25516e+06 | 28034.4 | 0.213656 | 0.155709 | 2(Loss) | true |
| Glaze | 2804.01 | 0.0781863 | 8149.4ms | 466906 | 640 | 9.86598e+06 | 158800 | 0.108909 | 0.882797 | 3(Loss) | true |
