
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3040.27 | 0.0474965 | 5802.21ms | 631514 | 1280 | 1.13311e+07 | 198094 | 0.00142371 | 0.814199 | 1(Win) | true |
| Jsonifier (two-stage) | 2640.72 | 0.188169 | 6636.14ms | 631514 | 80 | 1.47336e+07 | 228066 | 0.1067 | 0.937381 | 2(Loss) | true |
| Glaze | 2209.54 | 0.155295 | 7569.35ms | 631514 | 160 | 2.86682e+07 | 272572 | 0.17035 | 1.12039 | 3(Loss) | true |
| simdjson (ondemand) | 1355.18 | 0.0813929 | 6012.19ms | 631514 | 160 | 2.09348e+07 | 444414 | 0.0697613 | 1.82655 | 4(Loss) | true |
