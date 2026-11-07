
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16845.5 | 0.152274 | 4138.56ms | 716365 | 1280 | 4.88163e+06 | 40555.7 | 0.170929 | 0.146873 | 1(Win) | true |
| Glaze | 4536.89 | 0.170524 | 7595.12ms | 716365 | 1280 | 8.43979e+07 | 150583 | 0.79542 | 0.545546 | 2(Loss) | true |
