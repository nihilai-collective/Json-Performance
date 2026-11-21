
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1562.56 | 0.0311052 | 5941.91ms | 94653 | 30 | 9686.86 | 57769.4 | 0.0191026 | 1(Win) | true |
| Glaze | 1142.7 | 0.0569104 | 8153.18ms | 94653 | 2560 | 5.17404e+06 | 78995.7 | 4.68768 | 2(Loss) | true |
| Jsonifier (two-stage) | 1110.2 | 0.0562364 | 8243ms | 94653 | 4890 | 1.02237e+07 | 81307.7 | 0.0710207 | 3(Loss) | true |
| simdjson (ondemand) | 835.156 | 0.636025 | 5771.63ms | 94653 | 40 | 1.89035e+07 | 108085 | 0.796094 | 4(Loss) | true |
