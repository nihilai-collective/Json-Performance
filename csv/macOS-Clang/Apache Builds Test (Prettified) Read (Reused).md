
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2256.82 | 0.0771031 | 6836.55ms | 124597 | 2560 | 4.21897e+06 | 52651.6 | 0.0404532 | 1(Win) | true |
| Jsonifier (two-stage) | 1826.36 | 0.498062 | 8617.7ms | 124597 | 80 | 8.40038e+06 | 65061 | 0.196721 | 2(Loss) | true |
| Glaze | 1719.24 | 0.0723939 | 8421.22ms | 124597 | 4890 | 1.2242e+07 | 69114.7 | 0.274162 | 3(Loss) | true |
| simdjson (ondemand) | 1351.27 | 0.192711 | 5352.65ms | 124597 | 160 | 4.59478e+06 | 87935.9 | 0.00307032 | 4(Loss) | true |
