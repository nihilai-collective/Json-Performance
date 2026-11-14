
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1947 | 0.0481955 | 7136.09ms | 500299 | 1280 | 1.78546e+07 | 245055 | 0.134228 | 1.56091 | 1(Win) | true |
| Jsonifier (two-stage) | 1497.89 | 0.0577909 | 9051.34ms | 500299 | 1280 | 4.33739e+07 | 318529 | 0.094339 | 2.02884 | 2(Loss) | true |
| Glaze | 994.134 | 0.0470969 | 6576.71ms | 500299 | 640 | 3.26989e+07 | 479938 | 0.0116565 | 3.05721 | 3(Loss) | true |
| simdjson (ondemand) | 725.819 | 0.176322 | 8777.22ms | 500299 | 40 | 5.37374e+07 | 657358 | 0.00874791 | 4.18723 | 4(Loss) | true |
