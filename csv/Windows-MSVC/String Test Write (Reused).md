
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8544.83 | 0.254096 | 125.051ms | 9578 | 1280 | 9443.85 | 1068.98 | 0.313274 | 0.347054 | 1(Win) | true |
| Glaze | 3326.53 | 0.0830676 | 298.016ms | 9578 | 4890 | 25441.3 | 2745.89 | 0.0728215 | 0.90557 | 2(Loss) | true |
