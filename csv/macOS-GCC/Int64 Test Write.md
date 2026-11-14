
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 651.736 | 3.34144 | 546.836ms | 3862 | 40 | 1.42629e+06 | 5651.2 | 0.263554 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 633.992 | 0.27362 | 535.996ms | 3862 | 4890 | 1.23555e+06 | 5809.37 | 1.80078 | 1(Tie) | true |
| Glaze | 466.93 | 0.253183 | 840.986ms | 3862 | 4890 | 1.95029e+06 | 7887.89 | 0.682742 | 3(Loss) | true |
