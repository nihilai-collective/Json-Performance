
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1139.82 | 0.648326 | 106.28ms | 1213 | 2560 | 110834 | 1014.9 | 2.43238 | 1(Win) | true |
| Glaze | 851.595 | 1.05309 | 143.94ms | 1213 | 1280 | 261936 | 1358.4 | 0.0589275 | 2(Loss) | true |
| simdjson (reflection) | 733.549 | 0.869255 | 184.393ms | 1213 | 1280 | 240529 | 1577 | 0.165142 | 3(Loss) | true |
| simdjson (ondemand) | 277.794 | 1.8858 | 449.371ms | 1213 | 30 | 185007 | 4164.27 | 0.204499 | 4(Loss) | true |
