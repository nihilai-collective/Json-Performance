
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 625.083 | 0.153627 | 9868.15ms | 4203058 | 40 | 3.88197e+09 | 6.4125e+06 | 0.7651 | 1(Win) | true |
| simdjson (ondemand) | 529.367 | 0.103535 | 5384.57ms | 4203058 | 40 | 2.45838e+09 | 7.57197e+06 | 0.201271 | 2(Loss) | true |
