
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5052.25 | 1.73392 | 85.8301ms | 3862 | 1280 | 204514 | 729 | 0.690608 | 1(Win) | true |
| simdjson (reflection) | 3155.4 | 0.483884 | 127.345ms | 3862 | 4890 | 155994 | 1167.23 | 0.116862 | 2(Loss) | true |
| Glaze | 2252.24 | 0.625951 | 178.082ms | 3862 | 2560 | 268235 | 1635.3 | 0.177653 | 3(Loss) | true |
