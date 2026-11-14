
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3268.95 | 0.143711 | 5234.96ms | 699405 | 320 | 2.7515e+07 | 204042 | 0.417121 | 1(Win) | true |
| Glaze | 2542.01 | 0.172402 | 6843.34ms | 699405 | 40 | 8.18553e+06 | 262393 | 0.0118415 | 2(Loss) | true |
| simdjson (ondemand) | 1638.14 | 0.155937 | 5771.31ms | 767297 | 80 | 3.88163e+07 | 446697 | 0.257472 | 3(Loss) | true |
