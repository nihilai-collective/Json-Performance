
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 647.989 | 0.101358 | 588.596ms | 3873 | 30 | 1001.37 | 5700.07 | 0.603348 | 1(Win) | true |
| simdjson (ondemand) | 433.103 | 0.695584 | 911.869ms | 3873 | 160 | 563029 | 8528.17 | 1.57033 | 2(Loss) | true |
