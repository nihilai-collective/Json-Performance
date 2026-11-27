
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22472.8 | 0.723038 | 1987.7ms | 466906 | 160 | 3.28387e+06 | 19814 | 0.0468954 | 0.110007 | 1(Win) | true |
| simdjson (ondemand) | 21414.7 | 0.347663 | 1992.08ms | 466906 | 30 | 156774 | 20793 | 0.427281 | 0.115464 | 2(Loss) | true |
| Glaze | 2809.73 | 0.0900296 | 8152.34ms | 466906 | 640 | 1.3028e+07 | 158476 | 0.161349 | 0.880997 | 3(Loss) | true |
