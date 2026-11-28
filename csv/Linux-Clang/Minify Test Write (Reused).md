
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21832.5 | 0.0686021 | 2075.35ms | 466906 | 30 | 5872.82 | 20395.1 | 0.140523 | 0.113246 | 1(Win) | true |
| simdjson (ondemand) | 19801.2 | 0.0773286 | 2282.3ms | 466906 | 4890 | 1.47865e+06 | 22487.3 | 0.652701 | 0.124867 | 2(Loss) | true |
| Glaze | 2661.43 | 0.104134 | 8643.88ms | 466906 | 320 | 9.71326e+06 | 167307 | 0.00797498 | 0.930103 | 3(Loss) | true |
