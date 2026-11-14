
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2026.32 | 0.721768 | 179.2ms | 3862 | 4890 | 841612 | 1817.62 | 1.22053 | 1(Win) | true |
| Glaze | 1330.85 | 0.226595 | 279.473ms | 3862 | 2560 | 100672 | 2767.48 | 0.0407944 | 2(Loss) | true |
| Jsonifier (two-stage) | 863.375 | 0.215589 | 433.719ms | 3862 | 1280 | 108265 | 4265.92 | 0.165408 | 3(Loss) | true |
| simdjson (ondemand) | 494.509 | 0.101693 | 761.295ms | 3862 | 40 | 2294.64 | 7447.98 | 0.0830632 | 4(Loss) | true |
