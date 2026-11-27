
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2046.16 | 0.210073 | 5454.12ms | 466906 | 80 | 1.6719e+07 | 217616 | 0.100931 | 1(Win) | true |
| Jsonifier (two-stage) | 1712.25 | 0.674396 | 6371.93ms | 466906 | 160 | 4.92125e+08 | 260054 | 1.28198 | 2(Loss) | true |
| Glaze | 1633.42 | 0.725888 | 6857.91ms | 466906 | 80 | 3.13252e+08 | 272604 | 0.239398 | 3(Loss) | true |
| simdjson (ondemand) | 849.321 | 0.0866582 | 6908.45ms | 466906 | 160 | 3.30259e+07 | 524273 | 0.120868 | 4(Loss) | true |
