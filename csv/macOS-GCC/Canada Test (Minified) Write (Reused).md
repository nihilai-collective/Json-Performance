
----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1927.77 | 1.31758 | 5994.55ms | 2090234 | 40 | 7.42498e+09 | 1.03405e+06 | 1.24968 | 1(Win) | true |
| Glaze | 1536.14 | 1.21012 | 8204.72ms | 2090234 | 40 | 9.86383e+09 | 1.29767e+06 | 0.389323 | 2(Loss) | true |
| simdjson (reflection) | 700.758 | 1.15567 | 8602.45ms | 2090326 | 40 | 4.32333e+10 | 2.84476e+06 | 0.415668 | 3(Loss) | true |
