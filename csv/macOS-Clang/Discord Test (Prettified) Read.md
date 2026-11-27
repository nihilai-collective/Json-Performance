
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2412.01 | 0.0299851 | 3407.9ms | 83958 | 80 | 7926.25 | 33195.8 | 0.0222117 | 1(Win) | true |
| Jsonifier (two-stage) | 1975.61 | 0.0944808 | 4082.42ms | 83958 | 1280 | 1.8768e+06 | 40528.6 | 0.0479216 | 2(Loss) | true |
| Glaze | 1856.85 | 0.053175 | 4463.82ms | 83958 | 4890 | 2.57095e+06 | 43120.6 | 0.311147 | 3(Loss) | true |
| simdjson (ondemand) | 1113.32 | 0.0634467 | 7305.28ms | 83958 | 2560 | 5.33023e+06 | 71919.1 | 0.282657 | 4(Loss) | true |
