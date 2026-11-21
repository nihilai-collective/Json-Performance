
----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2872.5 | 0.299125 | 880.206ms | 26071 | 2560 | 1.71609e+06 | 8655.6 | 0.0808071 | 1(Win) | true |
| simdjson (ondemand) | 2572.08 | 0.419506 | 938.377ms | 26071 | 1280 | 2.10491e+06 | 9666.6 | 0.815569 | 2(Loss) | true |
