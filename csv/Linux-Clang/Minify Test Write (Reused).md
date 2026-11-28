
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 23488.8 | 0.437929 | 1919.22ms | 466906 | 80 | 551359 | 18957 | 0.0321885 | 0.105255 | 1(Win) | true |
| Jsonifier | 19950.4 | 0.0838582 | 2229.01ms | 466906 | 4890 | 1.713e+06 | 22319.2 | 0.607306 | 0.123933 | 2(Loss) | true |
| Glaze | 2536.18 | 0.134034 | 8754.25ms | 466906 | 640 | 3.54415e+07 | 175570 | 0.0136102 | 0.976031 | 3(Loss) | true |
