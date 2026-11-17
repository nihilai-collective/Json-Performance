
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 718.148 | 0.107301 | 7768.56ms | 461466 | 30 | 1.29713e+07 | 612810 | 0.213313 | 4.23201 | 1(Win) | true |
| Jsonifier (two-stage) | 654.932 | 0.127932 | 8546.26ms | 461466 | 80 | 5.91202e+07 | 671960 | 0.0531743 | 4.64029 | 2(Loss) | true |
| Glaze | 637.37 | 0.135164 | 8794.33ms | 461466 | 40 | 3.48399e+07 | 690475 | 0.166103 | 4.76811 | 3(Loss) | true |
| simdjson (ondemand) | 502.566 | 0.2658 | 5539.91ms | 461466 | 40 | 2.16703e+08 | 875682 | 0.421977 | 6.04732 | 4(Loss) | true |
