
----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3592.89 | 0.486575 | 6038.37ms | 238993 | 30 | 2.85827e+06 | 63436.8 | 0.0537779 | 1(Win) | true |
| simdjson (ondemand) | 3184.68 | 0.218948 | 7055.2ms | 238993 | 160 | 3.9286e+06 | 71568 | 0.129499 | 2(Loss) | true |
