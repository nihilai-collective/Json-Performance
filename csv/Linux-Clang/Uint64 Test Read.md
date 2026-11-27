
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2517.26 | 0.11798 | 48.6655ms | 1213 | 80 | 23.5165 | 459.55 | 0.0816682 | 0.928782 | 1(Win) | true |
| simdjson (stage-1) | 1153.92 | 0.111525 | 103.581ms | 1213 | 30 | 37.5 | 1002.5 | 0.0332392 | 2.09044 | 2(Loss) | true |
