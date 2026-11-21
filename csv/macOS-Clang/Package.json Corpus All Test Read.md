
----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3349.58 | 1.37568 | 6906.13ms | 238993 | 40 | 3.50499e+07 | 68044.8 | 0.507213 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 3270.67 | 0.500216 | 7382.45ms | 238993 | 1280 | 1.55533e+08 | 69686.5 | 2.01277 | 1(Tie) | true |
