
----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3800.79 | 0.293397 | 3882.71ms | 152326 | 320 | 4.02403e+06 | 38220.8 | 0.568349 | 1(Win) | true |
| simdjson (ondemand) | 3221.28 | 0.393823 | 4560.56ms | 152326 | 320 | 1.00935e+07 | 45096.8 | 0.636325 | 2(Loss) | true |
