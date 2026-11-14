
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 632.068 | 0.444647 | 6274.26ms | 83958 | 640 | 2.03052e+08 | 126677 | 0.200278 | 1(Win) | true |
| simdjson (ondemand) | 241.989 | 0.0684307 | 8740.98ms | 83958 | 1280 | 6.56213e+07 | 330877 | 0.0776725 | 2(Loss) | true |
