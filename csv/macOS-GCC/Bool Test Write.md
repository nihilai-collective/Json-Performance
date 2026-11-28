
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1762.1 | 2.0284 | 51.7251ms | 905 | 2560 | 252687 | 489.8 | 1.15655 | 1(Win) | true |
| simdjson (reflection) | 213.042 | 0.983323 | 421.966ms | 905 | 40 | 63477.5 | 4051.2 | 0.582627 | 2(Loss) | true |
| Glaze | 125.93 | 0.274251 | 710.621ms | 905 | 1280 | 452213 | 6853.6 | 0.302572 | 3(Loss) | true |
