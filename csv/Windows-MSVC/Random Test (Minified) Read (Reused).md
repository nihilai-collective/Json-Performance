
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 885.777 | 0.590405 | 7383.16ms | 461466 | 640 | 5.50695e+09 | 496839 | 0.532959 | 2.79487 | 1(Win) | true |
| Jsonifier (two-stage) | 804.391 | 0.220653 | 8187.13ms | 461466 | 40 | 5.8294e+07 | 547108 | 0.128846 | 3.07767 | 2(Loss) | true |
| Glaze | 780.24 | 0.100129 | 8398.98ms | 461466 | 320 | 1.02069e+08 | 564042 | 0.259462 | 3.17288 | 3(Loss) | true |
| simdjson (ondemand) | 604.565 | 0.234099 | 5223.32ms | 461466 | 80 | 2.32318e+08 | 727942 | 0.0964118 | 4.09503 | 4(Loss) | true |
