
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1778.7 | 0.0758171 | 439.49ms | 8051 | 40 | 428.438 | 4316.65 | 0.0962319 | 1(Win) | true |
| Jsonifier (two-stage) | 1324.04 | 0.272088 | 593.56ms | 8051 | 40 | 9958.15 | 5798.95 | 0.246339 | 2(Loss) | true |
| Glaze | 1263.83 | 0.151063 | 615.399ms | 8051 | 1280 | 107807 | 6075.21 | 0.23745 | 3(Loss) | true |
| simdjson (ondemand) | 1016.69 | 0.0800375 | 803.518ms | 8051 | 4890 | 178657 | 7552 | 0.888905 | 4(Loss) | true |
