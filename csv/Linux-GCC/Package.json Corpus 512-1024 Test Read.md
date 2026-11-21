
----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6582.1 | 0.0621417 | 394.378ms | 26071 | 40 | 220.4 | 3777.4 | 0.0989312 | 0.373574 | 1(Win) | true |
| Jsonifier (generic) | 6364.99 | 0.168971 | 423.413ms | 26071 | 2560 | 111528 | 3906.25 | 0.267212 | 0.386437 | 2(Loss) | true |
