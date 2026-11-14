
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 799.496 | 2.19983 | 6020.34ms | 409725 | 30 | 3.46778e+09 | 488738 | 1.17472 | 1(Win) | true |
| simdjson (ondemand) | 607.201 | 0.0822116 | 8292.89ms | 409725 | 320 | 8.95645e+07 | 643517 | 0.0407926 | 2(Loss) | true |
