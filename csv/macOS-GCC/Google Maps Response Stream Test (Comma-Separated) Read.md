
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 738.485 | 0.458162 | 8766.69ms | 4203058 | 40 | 2.4737e+10 | 5.4278e+06 | 0.671942 | 1(Win) | true |
| simdjson (ondemand) | 476.072 | 2.59135 | 5766.72ms | 4203058 | 40 | 1.90414e+12 | 8.41962e+06 | 1.36893 | 2(Loss) | true |
