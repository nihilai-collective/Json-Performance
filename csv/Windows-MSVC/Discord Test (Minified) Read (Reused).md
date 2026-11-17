
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1710.56 | 0.223923 | 3701.24ms | 56369 | 640 | 3.16946e+06 | 31427 | 0.858168 | 1.44606 | 1(Win) | true |
| Glaze | 1387.33 | 0.139539 | 4493.03ms | 56369 | 1280 | 3.74214e+06 | 38748.9 | 0.00685456 | 1.78329 | 2(Loss) | true |
| Jsonifier (two-stage) | 1252.33 | 0.119559 | 4833.14ms | 56369 | 2560 | 6.74299e+06 | 42926.3 | 0.0037311 | 1.97562 | 3(Loss) | true |
| simdjson (ondemand) | 890.809 | 0.0726658 | 6491.51ms | 56369 | 4890 | 9.40332e+06 | 60347 | 0.201007 | 2.77799 | 4(Loss) | true |
