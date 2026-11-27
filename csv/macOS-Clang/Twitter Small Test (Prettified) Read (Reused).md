
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2954.53 | 0.0498784 | 141.643ms | 3808 | 1280 | 481.119 | 1229.16 | 0.00489433 | 1(Win) | true |
| Jsonifier (two-stage) | 2669.42 | 0.0430243 | 156.576ms | 3808 | 1280 | 438.528 | 1360.44 | 0.00195245 | 2(Loss) | true |
| Glaze | 2362.82 | 0.148254 | 169.758ms | 3808 | 160 | 830.742 | 1536.97 | 0.166186 | 3(Loss) | true |
| simdjson (ondemand) | 1159.98 | 0.0451354 | 327.196ms | 3808 | 640 | 1277.93 | 3130.73 | 0.0538223 | 4(Loss) | true |
