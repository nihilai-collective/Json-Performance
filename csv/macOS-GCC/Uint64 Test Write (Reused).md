
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5046 | 0.889112 | 85.7971ms | 3873 | 4890 | 207120 | 731.982 | 0.464781 | 1(Win) | true |
| simdjson (reflection) | 3108.48 | 0.481451 | 129.752ms | 3873 | 4890 | 160034 | 1188.23 | 2.12526 | 2(Loss) | true |
| Glaze | 2415.05 | 0.961706 | 165.719ms | 3873 | 1280 | 276909 | 1529.4 | 3.75848 | 3(Loss) | true |
