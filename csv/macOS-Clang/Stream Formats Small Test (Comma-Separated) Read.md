
----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2513.39 | 0.122298 | 9173.51ms | 16002591 | 80 | 4.41153e+09 | 6.07199e+06 | 0.0407087 | 1(Win) | true |
| simdjson (ondemand) | 1427.48 | 0.161713 | 7561.39ms | 16002591 | 30 | 8.96711e+09 | 1.0691e+07 | 0.0569078 | 2(Loss) | true |
