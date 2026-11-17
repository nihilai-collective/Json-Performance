
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2802.24 | 0.125007 | 5256.91ms | 466906 | 1280 | 5.05042e+07 | 158900 | 1.66945 | 1(Win) | true |
| Jsonifier (two-stage) | 2230.57 | 0.246712 | 6205.84ms | 466906 | 160 | 3.88086e+07 | 199624 | 0.0457068 | 2(Loss) | true |
| Glaze | 1968.09 | 0.237296 | 7112.24ms | 466906 | 640 | 1.84471e+08 | 226248 | 0.606777 | 3(Loss) | true |
| simdjson (reflection) | 1349.74 | 1.54562 | 5055.74ms | 466906 | 30 | 7.79988e+08 | 329899 | 1.76598 | 4(Loss) | true |
| simdjson (ondemand) | 1016.36 | 0.424078 | 5978.5ms | 466906 | 320 | 1.10461e+09 | 438110 | 0.392487 | 5(Loss) | true |
