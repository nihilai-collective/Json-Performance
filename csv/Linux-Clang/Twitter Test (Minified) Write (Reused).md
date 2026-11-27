
----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17824.3 | 0.132667 | 2560.9ms | 475954 | 1280 | 1.46097e+06 | 25465.5 | 0.0184843 | 0.138753 | 1(Win) | true |
| Glaze | 6545.62 | 0.0717986 | 6943.21ms | 475954 | 4890 | 1.21219e+07 | 69344.9 | 0.0333858 | 0.37807 | 2(Loss) | true |
