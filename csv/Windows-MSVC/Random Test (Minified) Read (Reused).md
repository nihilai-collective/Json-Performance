
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 948.517 | 0.281587 | 7096.51ms | 461466 | 40 | 6.82768e+07 | 463975 | 0.226867 | 2.60999 | 1(Win) | true |
| Jsonifier (two-stage) | 854.708 | 0.188906 | 7736.93ms | 461466 | 80 | 7.56875e+07 | 514899 | 0.175341 | 2.89647 | 2(Loss) | true |
| Glaze | 820.938 | 0.205893 | 8148.13ms | 461466 | 40 | 4.87309e+07 | 536080 | 0.029216 | 3.0157 | 3(Loss) | true |
| simdjson (ondemand) | 636.092 | 0.107286 | 9989.51ms | 461466 | 160 | 8.81543e+07 | 691862 | 0.158198 | 3.89199 | 4(Loss) | true |
