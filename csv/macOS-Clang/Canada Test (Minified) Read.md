
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 475.361 | 0.788118 | 6351.12ms | 2090234 | 30 | 3.27677e+10 | 4.19345e+06 | 0.213698 | 1(Win) | true |
| simdjson (ondemand) | 463.053 | 0.843152 | 7020.71ms | 2090234 | 30 | 3.95241e+10 | 4.30491e+06 | 4.80172 | 2(Loss) | true |
