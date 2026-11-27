
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3312.87 | 0.138346 | 5454.27ms | 183677 | 4890 | 2.61664e+07 | 52875 | 0.462448 | 1(Win) | true |
| simdjson (ondemand) | 2622.51 | 0.294336 | 6637.48ms | 183677 | 640 | 2.47367e+07 | 66794 | 0.382399 | 2(Loss) | true |
