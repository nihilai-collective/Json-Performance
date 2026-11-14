
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 672.171 | 0.455128 | 528.104ms | 3873 | 1280 | 800596 | 5495 | 1.53363 | 1(Win) | true |
| simdjson (ondemand) | 446.365 | 0.198055 | 860.686ms | 3873 | 2560 | 687582 | 8274.8 | 0.622103 | 2(Loss) | true |
