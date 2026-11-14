
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 7647.04 | 0.232194 | 8003.84ms | 631514 | 320 | 1.07012e+07 | 78757.1 | 0.270606 | 1(Win) | true |
| Jsonifier | 7311.57 | 0.112478 | 8283.37ms | 631514 | 1280 | 1.09873e+07 | 82370.7 | 0.0948331 | 2(Loss) | true |
