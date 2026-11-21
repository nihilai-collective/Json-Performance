
----
### Package.json Corpus 0-512 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%200-512%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1769.88 | 0.602847 | 81.642ms | 1497 | 640 | 15133.9 | 806.638 | 1.65281 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1702.52 | 1.89304 | 75.1673ms | 1497 | 40 | 10079.4 | 838.55 | 0.457232 | 1(Tie) | true |
