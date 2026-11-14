
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2551.65 | 0.07478 | 2182.23ms | 56369 | 4890 | 1.21372e+06 | 21067.8 | 0.0251327 | 1(Win) | true |
| Glaze | 1588.43 | 0.126838 | 3448.59ms | 56369 | 30 | 55279 | 33843.2 | 0.497954 | 2(Loss) | true |
| Jsonifier (two-stage) | 1302.69 | 0.162728 | 4152.32ms | 56369 | 640 | 2.88604e+06 | 41266.6 | 0.0947962 | 3(Loss) | true |
| simdjson (ondemand) | 761.588 | 0.0890503 | 7071.5ms | 56369 | 2560 | 1.01147e+07 | 70586.3 | 0.0889752 | 4(Loss) | true |
