
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2206.64 | 0.285474 | 5638.43ms | 466906 | 40 | 1.32736e+07 | 201789 | 0.0290317 | 1.12179 | 1(Win) | true |
| Glaze | 2164.65 | 0.0751839 | 5909.93ms | 466906 | 640 | 1.53079e+07 | 205704 | 0.0502381 | 1.1436 | 2(Loss) | true |
| Jsonifier | 2150.22 | 0.144575 | 6050.28ms | 466906 | 320 | 2.86836e+07 | 207084 | 0.0777008 | 1.15124 | 3(Loss) | true |
| simdjson (ondemand) | 1029.93 | 0.0891738 | 5835.96ms | 466906 | 160 | 2.37815e+07 | 432337 | 0.0244079 | 2.40367 | 4(Loss) | true |
