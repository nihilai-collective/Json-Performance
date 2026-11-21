
----
### Package.json Corpus 0-512 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%200-512%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3116.82 | 0.30125 | 48.7391ms | 1497 | 1280 | 2437.15 | 458.047 | 0.153741 | 0.747094 | 1(Win) | true |
| Jsonifier (generic) | 2972.34 | 0.244829 | 51.9317ms | 1497 | 1280 | 1770.04 | 480.312 | 0.195567 | 0.78613 | 2(Loss) | true |
