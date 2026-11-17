
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2198.2 | 0.0843115 | 9924.05ms | 728486 | 1280 | 9.08851e+07 | 316049 | 0.696086 | 1.12617 | 1(Win) | true |
| Jsonifier | 1802.42 | 0.307872 | 5843.25ms | 728486 | 30 | 4.22467e+07 | 385449 | 0.267007 | 1.37347 | 2(Loss) | true |
| Glaze | 1619.27 | 0.115667 | 6398.42ms | 728486 | 160 | 3.94042e+07 | 429044 | 0.0516711 | 1.52885 | 3(Loss) | true |
| simdjson (ondemand) | 1535.88 | 0.14876 | 6767.03ms | 728486 | 30 | 1.35837e+07 | 452339 | 0.265473 | 1.61185 | 4(Loss) | true |
