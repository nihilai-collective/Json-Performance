
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 751.436 | 0.417403 | 502.449ms | 3862 | 1280 | 535749 | 4901.4 | 0.0693198 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 749.022 | 0.385729 | 498.342ms | 3862 | 1280 | 460480 | 4917.2 | 0.236464 | 1(Tie) | true |
| Glaze | 515.991 | 0.247682 | 725.634ms | 3862 | 2560 | 800149 | 7137.9 | 0.163646 | 3(Loss) | true |
