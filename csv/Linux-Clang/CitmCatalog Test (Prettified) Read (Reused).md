
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4171.71 | 0.0858878 | 7647.07ms | 1151920 | 1280 | 6.5477e+07 | 263335 | 0.233206 | 0.593396 | 1(Win) | true |
| Jsonifier | 3282.14 | 0.143461 | 9425.73ms | 1151920 | 1280 | 2.95126e+08 | 334707 | 0.144927 | 0.754256 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2561.88 | 0.103606 | 5962.08ms | 1151920 | 320 | 6.31609e+07 | 428809 | 0.186083 | 0.966319 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 2554.14 | 0.268498 | 6005.86ms | 1151920 | 40 | 5.33457e+07 | 430108 | 0.0499547 | 0.969267 | 3(Tie) | true |
