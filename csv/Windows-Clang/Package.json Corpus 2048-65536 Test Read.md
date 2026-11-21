
----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/Windows-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7957.11 | 0.644614 | 695.124ms | 59099 | 320 | 667112 | 7083.12 | 0.386745 | 0.309951 | 1(Win) | true |
| simdjson (ondemand) | 7269.29 | 0.119486 | 812.125ms | 59099 | 30 | 2574.71 | 7753.33 | 0.300043 | 0.33919 | 2(Loss) | true |
