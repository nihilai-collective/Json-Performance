
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2713.25 | 0.3812 | 5220.36ms | 466906 | 80 | 3.13095e+07 | 164112 | 0.265691 | 1(Win) | true |
| Jsonifier (two-stage) | 1968.74 | 0.577129 | 6634.89ms | 466906 | 640 | 1.09046e+09 | 226173 | 0.0171659 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 1827.82 | 0.911896 | 6806.56ms | 466906 | 80 | 3.94797e+08 | 243611 | 5.008 | -(Loss) | false |
| simdjson (ondemand) | 867.506 | 0.382941 | 7091.07ms | 466906 | 40 | 1.54539e+08 | 513283 | 0.376455 | 4(Loss) | true |
