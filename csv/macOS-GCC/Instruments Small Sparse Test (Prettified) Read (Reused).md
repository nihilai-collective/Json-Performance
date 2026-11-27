
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4753.27 | 0.471224 | 165.319ms | 7932 | 4890 | 275008 | 1591.44 | 0.0528411 | 1(Win) | true |
| simdjson (ondemand) | 4393.9 | 0.551106 | 178.239ms | 7932 | 2560 | 230449 | 1721.6 | 0.596003 | 2(Loss) | true |
