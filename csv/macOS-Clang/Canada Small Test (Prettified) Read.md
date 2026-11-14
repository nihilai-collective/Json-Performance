
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1024.96 | 0.0684994 | 1097.8ms | 11579 | 30 | 1633.89 | 10773.7 | 0.0910453 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1024.34 | 0.0417313 | 1091.82ms | 11579 | 80 | 1619.07 | 10780.2 | 0.0965663 | 1(Tie) | true |
