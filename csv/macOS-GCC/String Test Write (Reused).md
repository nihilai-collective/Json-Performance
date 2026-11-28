
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6122.05 | 2.04244 | 79.9409ms | 4215 | 1280 | 230202 | 656.6 | 1.11446 | 1(Win) | true |
| simdjson (reflection) | 5066.53 | 0.97254 | 90.028ms | 4215 | 4890 | 291137 | 793.391 | 0.114492 | 2(Loss) | true |
| Glaze | 2453.45 | 1.16912 | 195.803ms | 4215 | 640 | 234822 | 1638.4 | 0.53424 | 3(Loss) | true |
