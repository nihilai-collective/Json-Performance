
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6898.49 | 0.696994 | 6872.54ms | 466906 | 160 | 3.23839e+07 | 64546.9 | 2.1839 | 1(Win) | true |
| Jsonifier | 6248.51 | 0.153931 | 7476.12ms | 466906 | 4890 | 5.88396e+07 | 71261.2 | 0.868211 | 2(Loss) | true |
| Glaze | 1618.72 | 0.315828 | 7322.36ms | 466906 | 80 | 6.03821e+07 | 275080 | 0.132921 | 3(Loss) | true |
