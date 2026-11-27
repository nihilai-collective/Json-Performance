
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 24701.5 | 0.0728348 | 1807.81ms | 466906 | 4890 | 842949 | 18026.3 | 0.054838 | 0.100073 | 1(Win) | true |
| Jsonifier | 22840.5 | 0.037488 | 1970.51ms | 466906 | 30 | 1602.34 | 19495.1 | 0.0703236 | 0.108271 | 2(Loss) | true |
| Glaze | 2772.36 | 0.106987 | 8196.12ms | 466906 | 1280 | 3.77944e+07 | 160613 | 0.0717483 | 0.892884 | 3(Loss) | true |
