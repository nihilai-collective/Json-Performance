
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1813.59 | 0.194559 | 7990.53ms | 461466 | 80 | 1.78317e+07 | 242661 | 1.14853 | 1.36497 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1408.09 | 0.326159 | 9593.49ms | 461466 | 40 | 4.15662e+07 | 312544 | 0.393856 | 1.7581 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1406.32 | 0.205309 | 9640.15ms | 461466 | 80 | 3.30228e+07 | 312935 | 0.104924 | 1.7603 | 2(Tie) | true |
| simdjson (reflection) | 1361.78 | 0.0865692 | 9815.83ms | 461466 | 1280 | 1.00186e+08 | 323173 | 0.754719 | 1.81787 | 4(Loss) | true |
| Glaze | 1164.53 | 0.0715662 | 5683.79ms | 461466 | 640 | 4.68139e+07 | 377911 | 0.606242 | 2.12577 | 5(Loss) | true |
