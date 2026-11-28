
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1560.21 | 0.332654 | 76.565ms | 1213 | 4890 | 29747.6 | 741.444 | 0.334293 | 1.52945 | 1(Win) | true |
| Glaze | 891.734 | 0.161918 | 133.501ms | 1213 | 320 | 1411.85 | 1297.26 | 0.00963665 | 2.71821 | 2(Loss) | true |
| simdjson (ondemand) | 302.805 | 0.130927 | 384.627ms | 1213 | 40 | 1000.73 | 3820.3 | 0.0139625 | 8.12133 | 3(Loss) | true |
