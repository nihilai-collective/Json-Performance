
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2808.08 | 1.72437 | 50.3212ms | 1213 | 4890 | 246758 | 411.956 | 3.1695 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2796.92 | 3.34273 | 51.1649ms | 1213 | 1280 | 244665 | 413.6 | 0.289296 | 1(Tie) | true |
| Glaze | 1092.6 | 0.345941 | 123.087ms | 1213 | 4890 | 65600.8 | 1058.76 | 0.370607 | 3(Loss) | true |
