
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 6951.65 | 0.276473 | 2542.43ms | 183677 | 640 | 3.10612e+06 | 25198 | 0.0150163 | 1(Win) | true |
| Jsonifier | 6203.68 | 0.0993904 | 2854.47ms | 183677 | 4890 | 3.85132e+06 | 28236.2 | 0.0826097 | 2(Loss) | true |
