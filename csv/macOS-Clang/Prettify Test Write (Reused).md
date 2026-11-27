
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3410.82 | 0.0709939 | 5146.64ms | 699405 | 1280 | 2.46713e+07 | 195555 | 0.374046 | 1(Win) | true |
| Glaze | 2516.6 | 0.121747 | 7179.43ms | 699405 | 160 | 1.66597e+07 | 265042 | 0.146716 | 2(Loss) | true |
| simdjson (ondemand) | 1642.34 | 0.139397 | 5762.41ms | 767297 | 80 | 3.08599e+07 | 445553 | 0.26299 | 3(Loss) | true |
