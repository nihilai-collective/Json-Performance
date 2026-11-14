
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2703.15 | 0.344209 | 6444.96ms | 631514 | 40 | 2.3525e+07 | 222799 | 0.0216554 | 1(Win) | true |
| Jsonifier (two-stage) | 2674.36 | 0.0700175 | 6687.24ms | 631514 | 1280 | 3.18235e+07 | 225197 | 0.193897 | 2(Loss) | true |
| Glaze | 2268.97 | 0.086443 | 7529.89ms | 631514 | 1280 | 6.73875e+07 | 265433 | 0.58605 | 3(Loss) | true |
| simdjson (ondemand) | 1191.34 | 0.16198 | 6826.29ms | 631514 | 30 | 2.0116e+07 | 505532 | 0.0817742 | 4(Loss) | true |
