
----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8911.41 | 0.0751599 | 2592.08ms | 238993 | 4890 | 1.80701e+06 | 25576.4 | 0.385071 | 0.277541 | 1(Win) | true |
| simdjson (ondemand) | 7779.57 | 0.168657 | 2949.4ms | 238993 | 1280 | 3.12522e+06 | 29297.5 | 0.62745 | 0.317969 | 2(Loss) | true |
