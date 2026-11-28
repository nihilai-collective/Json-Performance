
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1263.3 | 0.118942 | 71.6362ms | 905 | 640 | 422.604 | 683.189 | 0.284633 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1261.57 | 0.0649105 | 74.5503ms | 905 | 2560 | 504.83 | 684.129 | 0.031471 | 1(Tie) | true |
| simdjson (ondemand) | 309.84 | 0.114307 | 326.082ms | 905 | 40 | 405.536 | 2785.55 | 0.0185447 | 3(Loss) | true |
