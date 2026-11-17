
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1069 | 0.373136 | 4897.83ms | 56369 | 1280 | 4.50682e+07 | 50287.8 | 0.0215976 | 1(Win) | true |
| simdjson (ondemand) | 866.369 | 0.184402 | 6111.23ms | 56369 | 4890 | 6.40196e+07 | 62049.4 | 1.5983 | 2(Loss) | true |
