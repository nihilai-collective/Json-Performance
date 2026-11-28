
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 754.909 | 1.58895 | 573.918ms | 4215 | 40 | 286342 | 5324.8 | 0.16 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 740.665 | 2.50213 | 518.885ms | 4215 | 30 | 553214 | 5427.2 | 1.39535 | 1(Tie) | true |
| Glaze | 460.346 | 0.758076 | 880.041ms | 4215 | 320 | 1.40218e+06 | 8732 | 1.15015 | 3(Loss) | true |
