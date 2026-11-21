
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1667.93 | 0.316889 | 7268.08ms | 124597 | 80 | 4.07722e+06 | 71241.1 | 0.00822842 | 1(Win) | true |
| Jsonifier (two-stage) | 1382.05 | 0.0528245 | 8723.52ms | 124597 | 2560 | 5.28053e+06 | 85977.2 | 0.104472 | 2(Loss) | true |
| Glaze | 1361.69 | 0.0688158 | 8874.31ms | 124597 | 4890 | 1.76338e+07 | 87263 | 0.0431054 | 3(Loss) | true |
| simdjson (ondemand) | 1113.2 | 0.0673916 | 5490.97ms | 124597 | 2560 | 1.3247e+07 | 106741 | 0.0365517 | 4(Loss) | true |
