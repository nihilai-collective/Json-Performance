
----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10587.3 | 0.0474982 | 556.878ms | 59099 | 40 | 255.741 | 5323.45 | 0.0910234 | 0.232683 | 1(Win) | true |
| simdjson (ondemand) | 8617.92 | 0.0442543 | 661.619ms | 59099 | 80 | 670.127 | 6540 | 0.256774 | 0.286173 | 2(Loss) | true |
