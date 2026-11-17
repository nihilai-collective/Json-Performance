
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2016.81 | 0.432359 | 3997.48ms | 83958 | 1280 | 3.77131e+07 | 39700.6 | 3.08223 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1526.25 | 1.04189 | 5292.52ms | 83958 | 80 | 2.39004e+07 | 52460.9 | 1.43088 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1504.92 | 0.245949 | 5016.34ms | 83958 | 4890 | 8.37333e+07 | 53204.7 | 0.132573 | 2(Tie) | true |
| simdjson (ondemand) | 946.397 | 1.20459 | 8426.13ms | 83958 | 80 | 8.30889e+07 | 84603.6 | 3.33807 | 4(Loss) | true |
