
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17997.4 | 2.0269 | 53.8801ms | 9249 | 2560 | 252624 | 490.1 | 0.0611746 | 1(Win) | true |
| Glaze | 2299.27 | 0.336343 | 374.714ms | 9249 | 4890 | 814112 | 3836.23 | 2.89744 | 2(Loss) | true |
| simdjson (reflection) | 328.353 | 0.25413 | 2738.39ms | 9249 | 30 | 139810 | 26862.9 | 0.0317561 | 3(Loss) | true |
