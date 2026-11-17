
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2154.8 | 0.0998587 | 180.425ms | 3873 | 160 | 468.785 | 1714.12 | 0.568833 | 1(Win) | true |
| Glaze | 1148.69 | 0.433866 | 332.495ms | 3873 | 640 | 124562 | 3215.48 | 1.72706 | 2(Loss) | true |
| Jsonifier (two-stage) | 768.824 | 0.391624 | 534.348ms | 3873 | 1280 | 453095 | 4804.19 | 1.31893 | 3(Loss) | true |
| simdjson (ondemand) | 475.911 | 0.108792 | 863.773ms | 3873 | 30 | 2138.75 | 7761.07 | 1.25409 | 4(Loss) | true |
