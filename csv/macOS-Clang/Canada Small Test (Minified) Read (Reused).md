
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 717.469 | 0.311989 | 782.751ms | 4630 | 2560 | 943788 | 6154.29 | 1.17477 | 1(Win) | true |
| Jsonifier (two-stage) | 642.475 | 0.751492 | 853.934ms | 4630 | 160 | 426793 | 6872.66 | 0.22394 | 2(Loss) | true |
| Glaze | 528.279 | 0.187824 | 1062.76ms | 4630 | 30 | 7393.67 | 8358.3 | 0.233045 | 3(Loss) | true |
| simdjson (ondemand) | 436.966 | 0.944728 | 1159.3ms | 4630 | 160 | 1.45814e+06 | 10104.9 | 3.18148 | 4(Loss) | true |
