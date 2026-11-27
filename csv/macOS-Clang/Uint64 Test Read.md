
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 1581.96 | 0.318968 | 81.9956ms | 1213 | 80 | 435.228 | 731.25 | 0.851636 | 1(Win) | true |
| simdjson (stage-1) | 778.002 | 0.206044 | 166.924ms | 1213 | 4890 | 45897.6 | 1486.89 | 1.7354 | 2(Loss) | true |
