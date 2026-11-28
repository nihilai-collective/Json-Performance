
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 279.803 | 0.954264 | 457.515ms | 1313 | 160 | 291797 | 4475.2 | 0.320741 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 275.444 | 0.279867 | 448.347ms | 1313 | 4890 | 791544 | 4546.02 | 3.87144 | 1(Tie) | true |
| Glaze | 177.382 | 0.825563 | 703.685ms | 1313 | 320 | 1.08683e+06 | 7059.2 | 2.17693 | 3(Loss) | true |
