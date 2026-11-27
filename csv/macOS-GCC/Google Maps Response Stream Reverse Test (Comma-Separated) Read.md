
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 575.137 | 0.288884 | 5214.1ms | 4203058 | 40 | 1.62142e+10 | 6.96938e+06 | 0.671606 | 1(Win) | true |
| simdjson (ondemand) | 451.088 | 0.656614 | 6766.63ms | 4203058 | 30 | 1.02129e+11 | 8.88596e+06 | 3.01456 | 2(Loss) | true |
