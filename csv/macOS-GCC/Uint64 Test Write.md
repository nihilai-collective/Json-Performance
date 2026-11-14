
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 769.496 | 1.01964 | 498.687ms | 3873 | 80 | 191631 | 4800 | 0.398406 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 762.632 | 0.626899 | 517.442ms | 3873 | 320 | 294992 | 4843.2 | 0.9 | 1(Tie) | true |
| Glaze | 535.643 | 0.4572 | 736.642ms | 3873 | 640 | 636117 | 6895.6 | 0.261719 | 3(Loss) | true |
