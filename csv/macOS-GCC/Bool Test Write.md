
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1748.18 | 2.14076 | 53.374ms | 905 | 2560 | 285959 | 493.7 | 3.93684 | 1(Win) | true |
| simdjson (reflection) | 220.577 | 0.300628 | 402.345ms | 905 | 1280 | 177111 | 3912.8 | 0.102333 | 2(Loss) | true |
| Glaze | 127.28 | 0.135533 | 680.285ms | 905 | 4890 | 413025 | 6780.91 | 0.431163 | 3(Loss) | true |
