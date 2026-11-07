
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1327.2 | 0.365496 | 8628.39ms | 466906 | 1280 | 1.92468e+09 | 335500 | 0.334061 | 1.86513 | 1(Win) | true |
| Jsonifier (two-stage) | 1189.49 | 0.333745 | 9866.31ms | 466906 | 40 | 6.24348e+07 | 374342 | 0.301657 | 2.08105 | 2(Loss) | true |
| Glaze | 1126.42 | 0.389504 | 5061.87ms | 466906 | 640 | 1.51727e+09 | 395302 | 0.292509 | 2.19768 | 3(Loss) | true |
| simdjson (ondemand) | 948.419 | 0.311773 | 6087.05ms | 466906 | 30 | 6.42772e+07 | 469493 | 0.0447091 | 2.61022 | 4(Loss) | true |
