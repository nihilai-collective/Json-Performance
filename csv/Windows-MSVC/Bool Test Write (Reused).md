
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1648.37 | 0.226743 | 60.6974ms | 905 | 1280 | 1804.12 | 523.594 | 0.327186 | 1.78307 | 1(Win) | true |
| Glaze | 552.575 | 0.10264 | 168.333ms | 905 | 2560 | 6579.38 | 1561.91 | 0.579343 | 5.43237 | 2(Loss) | true |
