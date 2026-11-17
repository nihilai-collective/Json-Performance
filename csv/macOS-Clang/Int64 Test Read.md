
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2054.63 | 0.236439 | 183.42ms | 3862 | 2560 | 45986.9 | 1792.58 | 0.208976 | 1(Win) | true |
| Glaze | 1130.47 | 0.45934 | 320.379ms | 3862 | 640 | 143336 | 3258.01 | 2.44582 | 2(Loss) | true |
| Jsonifier (two-stage) | 820.976 | 0.128537 | 495.14ms | 3862 | 30 | 997.564 | 4486.23 | 0.0349338 | 3(Loss) | true |
| simdjson (ondemand) | 429.199 | 0.178227 | 849.358ms | 3862 | 4890 | 1.14383e+06 | 8581.31 | 0.32404 | 4(Loss) | true |
