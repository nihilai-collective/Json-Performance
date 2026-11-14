
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1185.7 | 0.11396 | 5770.45ms | 461466 | 80 | 1.43128e+07 | 371162 | 0.0451081 | 2.56323 | 1(Win) | true |
| Jsonifier (two-stage) | 1020.4 | 0.0748593 | 6534.35ms | 461466 | 320 | 3.33565e+07 | 431290 | 0.220392 | 2.97833 | 2(Loss) | true |
| Glaze | 973.704 | 0.0751028 | 6778.09ms | 461466 | 320 | 3.68712e+07 | 451973 | 0.0195708 | 3.12131 | 3(Loss) | true |
| simdjson (ondemand) | 739.009 | 0.150195 | 8625.66ms | 461466 | 160 | 1.28001e+08 | 595511 | 0.143578 | 4.11255 | 4(Loss) | true |
