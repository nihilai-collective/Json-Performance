
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4619.6 | 0.138435 | 175.127ms | 7932 | 80 | 411.088 | 1637.49 | 0.000763359 | 1(Win) | true |
| simdjson (ondemand) | 4537.38 | 0.0574881 | 175.802ms | 7932 | 320 | 293.942 | 1667.16 | 0.0146228 | 2(Loss) | true |
