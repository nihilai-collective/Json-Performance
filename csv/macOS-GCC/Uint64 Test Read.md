
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1139.04 | 0.963638 | 109.068ms | 1213 | 1280 | 122598 | 1015.6 | 0.833995 | 1(Win) | true |
| Glaze STATISTICAL TIE | 765.762 | 0.65073 | 157.298ms | 1213 | 4890 | 472547 | 1510.66 | 0.907723 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 723.004 | 5.05153 | 188.48ms | 1213 | 40 | 261304 | 1600 | 0.26738 | 2(Tie) | true |
| simdjson (ondemand) | 238.694 | 1.27363 | 453.335ms | 1213 | 320 | 1.21919e+06 | 4846.4 | 0.980713 | 4(Loss) | true |
