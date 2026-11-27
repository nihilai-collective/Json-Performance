
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1727.12 | 1.02519 | 69.942ms | 1213 | 4890 | 230566 | 669.788 | 0.874924 | 1(Win) | true |
| Glaze | 1026.33 | 0.440883 | 115.469ms | 1213 | 4890 | 120755 | 1127.13 | 0.54417 | 2(Loss) | true |
| simdjson (reflection) | 876.51 | 0.517456 | 135.882ms | 1213 | 4890 | 228067 | 1319.79 | 0.341163 | 3(Loss) | true |
| simdjson (ondemand) | 311.948 | 0.237688 | 375.062ms | 1213 | 4890 | 379912 | 3708.34 | 0.336464 | 4(Loss) | true |
