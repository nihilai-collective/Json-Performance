
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 528.138 | 0.194996 | 5719.3ms | 2090234 | 80 | 4.3335e+09 | 3.7744e+06 | 0.156783 | 1(Win) | true |
| simdjson (ondemand) | 493.482 | 0.150289 | 6151.23ms | 2090234 | 30 | 1.10566e+09 | 4.03946e+06 | 0.00505869 | 2(Loss) | true |
