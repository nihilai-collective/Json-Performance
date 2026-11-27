
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1805.43 | 1.33301 | 7858.95ms | 500299 | 160 | 1.98555e+09 | 264270 | 1.07064 | 1.68309 | 1(Win) | true |
| Jsonifier (two-stage) | 1289.63 | 0.791485 | 5208.89ms | 500299 | 640 | 5.48772e+09 | 369967 | 0.721052 | 2.35599 | 2(Loss) | true |
| Glaze | 901.068 | 2.02342 | 7377.88ms | 500299 | 40 | 4.59173e+09 | 529508 | 0.152102 | 3.37274 | 3(Loss) | true |
| simdjson (ondemand) | 630.748 | 0.575469 | 5089.92ms | 500299 | 320 | 6.06374e+09 | 756438 | 1.78898 | 4.818 | 4(Loss) | true |
