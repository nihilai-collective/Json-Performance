
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 1033.25 | 1.60941 | 201.84ms | 1997 | 160 | 140799 | 1843.2 | 0.348432 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1009.17 | 0.396356 | 202.36ms | 1997 | 4890 | 273593 | 1887.18 | 0.886104 | 1(Tie) | true |
| Glaze | 656.071 | 1.03645 | 286.794ms | 1798 | 320 | 234814 | 2613.6 | 0.0919118 | 3(Loss) | true |
