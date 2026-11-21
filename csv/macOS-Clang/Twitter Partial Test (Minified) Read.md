
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4920.12 | 0.0884841 | 9194ms | 466906 | 4890 | 3.13579e+07 | 90501 | 0.619884 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4899.14 | 0.682992 | 9273.36ms | 466906 | 40 | 1.54138e+07 | 90888.6 | 0.162072 | 1(Tie) | true |
| simdjson (ondemand) | 3600.59 | 0.239459 | 6301.21ms | 466906 | 1280 | 1.12249e+08 | 123668 | 0.336727 | 3(Loss) | true |
| Glaze | 2100.82 | 0.339823 | 5296.57ms | 466906 | 160 | 8.30052e+07 | 211953 | 1.31581 | 4(Loss) | true |
