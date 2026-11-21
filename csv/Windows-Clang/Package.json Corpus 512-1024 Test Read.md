
----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4653.13 | 0.194187 | 546.923ms | 26071 | 30 | 3229.89 | 5343.33 | 0 | 0.52855 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 4637.58 | 0.112492 | 528.266ms | 26071 | 80 | 2909.81 | 5361.25 | 0.304022 | 0.531223 | 1(Tie) | true |
