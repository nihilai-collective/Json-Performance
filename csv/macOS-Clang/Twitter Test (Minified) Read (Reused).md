
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2432.93 | 1.2148 | 10050ms | 466906 | 40 | 1.97729e+08 | 183021 | 0.404553 | 1(Win) | true |
| Jsonifier (two-stage) | 2171.62 | 0.344733 | 6033.33ms | 466906 | 30 | 1.49892e+07 | 205043 | 0.776331 | 2(Loss) | true |
| Glaze | 2108.51 | 0.293389 | 6661.8ms | 466906 | 320 | 1.22842e+08 | 211180 | 1.08891 | 3(Loss) | true |
| simdjson (ondemand) | 917.59 | 0.0966784 | 6893.68ms | 466906 | 160 | 3.5216e+07 | 485267 | 0.0196387 | 4(Loss) | true |
