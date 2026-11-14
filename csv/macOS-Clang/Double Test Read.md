
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 944.478 | 0.768141 | 175.207ms | 1811 | 640 | 126274 | 1828.63 | 0.177359 | 1(Win) | true |
| simdjson (stage-1) | 639.559 | 0.412144 | 271.584ms | 1811 | 1280 | 158557 | 2700.46 | 0.149097 | 2(Loss) | true |
