
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4943.54 | 0.223194 | 9122.41ms | 466906 | 80 | 3.23323e+06 | 90072.3 | 0.0479428 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4925.24 | 0.131975 | 9141.16ms | 466906 | 640 | 9.11111e+06 | 90407.1 | 0.239131 | 1(Tie) | true |
| simdjson (ondemand) | 4074.43 | 0.112666 | 5637.77ms | 466906 | 1280 | 1.94054e+07 | 109286 | 0.170929 | 3(Loss) | true |
| Glaze | 2301.68 | 0.204909 | 10017.8ms | 466906 | 80 | 1.25713e+07 | 193457 | 0.0455348 | 4(Loss) | true |
