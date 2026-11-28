
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 259.106 | 0.26247 | 458.278ms | 1213 | 4890 | 671484 | 4464.61 | 4.24265 | 1(Win) | true |
| Jsonifier | 222.258 | 0.473552 | 495.319ms | 1213 | 1280 | 777596 | 5204.8 | 0.564186 | 2(Loss) | true |
| Glaze | 147.516 | 0.378157 | 777.101ms | 1213 | 4890 | 4.30029e+06 | 7841.92 | 0.0748754 | 3(Loss) | true |
