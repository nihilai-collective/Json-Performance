
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1477.37 | 0.183017 | 80.4746ms | 1213 | 160 | 328.585 | 783.019 | 0.160695 | 1(Win) | true |
| Glaze | 794.647 | 0.266282 | 157.287ms | 1213 | 80 | 1202.11 | 1455.75 | 0.104647 | 2(Loss) | true |
| simdjson (ondemand) | 288.523 | 0.0667371 | 405.793ms | 1213 | 80 | 572.777 | 4009.41 | 0.0246235 | 3(Loss) | true |
