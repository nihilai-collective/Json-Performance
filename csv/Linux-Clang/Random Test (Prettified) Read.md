
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1875.3 | 0.0327511 | 8933.45ms | 676745 | 1280 | 1.62618e+07 | 344154 | 0.158705 | 1.32007 | 1(Win) | true |
| simdjson (ondemand) | 1695.39 | 0.0587153 | 9760.7ms | 676745 | 640 | 3.19738e+07 | 380676 | 0.183859 | 1.46013 | 2(Loss) | true |
