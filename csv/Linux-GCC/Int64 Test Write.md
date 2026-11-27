
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 333.087 | 0.0696487 | 373.848ms | 1313 | 30 | 205.666 | 3759.3 | 0.338081 | 7.3788 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 332.931 | 3.05013 | 397.582ms | 1313 | 160 | 2.10561e+06 | 3761.06 | 1.64553 | 7.38467 | 1(Tie) | true |
| Glaze | 309.324 | 0.0735993 | 411.609ms | 1313 | 40 | 355.067 | 4048.1 | 0.057607 | 7.95089 | 3(Loss) | true |
