
----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6721.09 | 0.0700607 | 358.999ms | 26071 | 80 | 537.372 | 3699.29 | 0.49928 | 0.365611 | 1(Win) | true |
| simdjson (ondemand) | 6507.51 | 0.0733145 | 381.727ms | 26071 | 30 | 235.39 | 3820.7 | 0.106325 | 0.377863 | 2(Loss) | true |
