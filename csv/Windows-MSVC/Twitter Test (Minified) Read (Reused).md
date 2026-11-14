
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2142.07 | 0.0651949 | 6179.79ms | 466906 | 1280 | 2.35086e+07 | 207872 | 0.0293815 | 1.41876 | 1(Win) | true |
| Glaze | 1751.82 | 0.144656 | 7383.57ms | 466906 | 80 | 1.08154e+07 | 254179 | 0.00442582 | 1.73483 | 2(Loss) | true |
| Jsonifier (two-stage) | 1656.93 | 0.103924 | 7754.23ms | 466906 | 640 | 4.99185e+07 | 268736 | 0.05806 | 1.83416 | 3(Loss) | true |
| simdjson (ondemand) | 1266.8 | 0.1541 | 9712.93ms | 466906 | 320 | 9.38863e+07 | 351498 | 0.18598 | 2.39875 | 4(Loss) | true |
