
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 843.09 | 0.188559 | 6654.48ms | 461466 | 320 | 3.10009e+08 | 521994 | 0.0662563 | 3.60464 | 1(Win) | true |
| Jsonifier (two-stage) | 751.079 | 0.159496 | 7457.41ms | 461466 | 320 | 2.79483e+08 | 585941 | 0.479189 | 4.04619 | 2(Loss) | true |
| Glaze | 732.943 | 0.223063 | 7648.34ms | 461466 | 320 | 5.74042e+08 | 600440 | 0.339066 | 4.14637 | 3(Loss) | true |
| simdjson (ondemand) | 584.918 | 0.110888 | 9555.74ms | 461466 | 640 | 4.45493e+08 | 752393 | 0.0476999 | 5.19579 | 4(Loss) | true |
