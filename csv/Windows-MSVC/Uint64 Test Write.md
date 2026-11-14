
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 516.275 | 0.0509406 | 719.365ms | 3873 | 4890 | 64948.8 | 7154.29 | 0.15649 | 5.86909 | 1(Win) | true |
| Glaze | 429.338 | 0.0986555 | 853.965ms | 3873 | 1280 | 92203.8 | 8602.97 | 0.0290682 | 7.06025 | 2(Loss) | true |
