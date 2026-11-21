
----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6153.69 | 0.136385 | 3725.89ms | 238993 | 2560 | 6.53236e+06 | 37038.2 | 0.0212995 | 0.402018 | 1(Win) | true |
| simdjson (ondemand) | 5622.58 | 0.0912337 | 4060.22ms | 238993 | 4890 | 6.68835e+06 | 40536.8 | 0.0325168 | 0.440028 | 2(Loss) | true |
