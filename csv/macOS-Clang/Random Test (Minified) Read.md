
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 985.493 | 0.488989 | 5150.71ms | 409725 | 160 | 6.01445e+08 | 396496 | 0.20809 | 1(Win) | true |
| simdjson (ondemand) | 732.664 | 0.253232 | 7145.76ms | 409725 | 160 | 2.91831e+08 | 533320 | 0.0135208 | 2(Loss) | true |
