
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3248.54 | 0.0597369 | 3506.3ms | 108313 | 4890 | 1.76433e+06 | 31797.5 | 1.55196 | 1(Win) | true |
| Jsonifier (two-stage) | 1941.94 | 0.0523493 | 5636.15ms | 108313 | 4890 | 3.79159e+06 | 53191.9 | 0.0591466 | 2(Loss) | true |
| Glaze | 1399.14 | 0.381237 | 6855.06ms | 108313 | 640 | 5.07003e+07 | 73827.9 | 0.106545 | 3(Loss) | true |
| simdjson (ondemand) | 570.95 | 1.06203 | 7935.28ms | 108313 | 160 | 5.90684e+08 | 180918 | 0.0877251 | 4(Loss) | true |
