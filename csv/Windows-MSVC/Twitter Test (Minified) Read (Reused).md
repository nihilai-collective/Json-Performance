
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1797.12 | 0.156782 | 7504.21ms | 466906 | 320 | 4.82887e+07 | 247772 | 0.284732 | 1.3775 | 1(Win) | true |
| Jsonifier (two-stage) | 1502.41 | 0.103398 | 8789.59ms | 466906 | 640 | 6.01016e+07 | 296374 | 0.0494763 | 1.64771 | 2(Loss) | true |
| Glaze | 1398.95 | 0.34185 | 9370.19ms | 466906 | 30 | 3.55179e+07 | 318293 | 0.589252 | 1.76954 | 3(Loss) | true |
| simdjson (ondemand) | 1101.62 | 0.0842297 | 5522.13ms | 466906 | 640 | 7.41828e+07 | 404200 | 0.338449 | 2.2472 | 4(Loss) | true |
