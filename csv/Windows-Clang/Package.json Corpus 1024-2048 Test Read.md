
----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6046.27 | 0.199032 | 2388.05ms | 152326 | 2560 | 5.85408e+06 | 24026.3 | 0.255417 | 0.408982 | 1(Win) | true |
| simdjson (ondemand) | 5696.56 | 0.507059 | 2604.71ms | 152326 | 160 | 2.67522e+06 | 25501.2 | 0.093046 | 0.434149 | 2(Loss) | true |
