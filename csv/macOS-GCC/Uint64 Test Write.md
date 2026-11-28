
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 238.789 | 0.250668 | 503.133ms | 1213 | 4890 | 721104 | 4844.47 | 2.51001 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 235.737 | 1.37311 | 497.704ms | 1213 | 160 | 726437 | 4907.2 | 0.163292 | 1(Tie) | true |
| Glaze | 146.654 | 1.52432 | 781.824ms | 1213 | 80 | 1.15658e+06 | 7888 | 0.524617 | 3(Loss) | true |
