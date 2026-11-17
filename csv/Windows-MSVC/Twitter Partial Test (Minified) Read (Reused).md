
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6842.64 | 0.0814115 | 6615.58ms | 466906 | 4890 | 1.37244e+07 | 65073.8 | 0.04441 | 0.443995 | 1(Win) | true |
| Jsonifier | 6799.15 | 0.244496 | 6610.44ms | 466906 | 40 | 1.02554e+06 | 65490 | 0.00508958 | 0.446856 | 2(Loss) | true |
| simdjson (ondemand) | 4349.94 | 0.185809 | 5305.83ms | 466906 | 160 | 5.78824e+06 | 102364 | 0.0439416 | 0.698552 | 3(Loss) | true |
| Glaze | 2958.62 | 0.156294 | 7783.15ms | 466906 | 1280 | 7.08228e+07 | 150501 | 0.767467 | 1.02707 | 4(Loss) | true |
