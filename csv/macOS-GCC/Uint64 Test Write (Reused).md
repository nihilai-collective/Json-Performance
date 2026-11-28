
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2340.76 | 1.45464 | 61.728ms | 1213 | 4890 | 252712 | 494.2 | 0.406422 | 1(Win) | true |
| simdjson (reflection) | 2121.43 | 1.32909 | 69.5729ms | 1213 | 4890 | 256853 | 545.296 | 1.0173 | 2(Loss) | true |
| Glaze | 830.801 | 0.535857 | 161.092ms | 1213 | 4890 | 272229 | 1392.4 | 1.29729 | 3(Loss) | true |
