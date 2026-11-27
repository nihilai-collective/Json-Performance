
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1286.7 | 0.0325497 | 4225.19ms | 56369 | 80 | 14794.9 | 41779.6 | 0.0432515 | 1(Win) | true |
| simdjson (ondemand) | 1027.29 | 0.0659579 | 5356.08ms | 56369 | 4890 | 5.82557e+06 | 52329.7 | 0.22134 | 2(Loss) | true |
