
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6632.9 | 0.0429558 | 6710.83ms | 466906 | 2560 | 2.1288e+06 | 67131.5 | 0.125844 | 0.458064 | 1(Win) | true |
| Jsonifier | 6579.31 | 0.0827473 | 6775.79ms | 466906 | 640 | 2.00718e+06 | 67678.3 | 0.179986 | 0.461793 | 2(Loss) | true |
| simdjson (ondemand) | 4199.1 | 0.0498714 | 5433.59ms | 466906 | 640 | 1.7899e+06 | 106041 | 0.065233 | 0.72367 | 3(Loss) | true |
| Glaze | 2849.29 | 0.465654 | 8109.14ms | 466906 | 160 | 8.47292e+07 | 156276 | 0.0608268 | 1.06652 | 4(Loss) | true |
