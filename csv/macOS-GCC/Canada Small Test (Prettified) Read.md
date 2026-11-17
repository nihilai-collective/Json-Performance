
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1293.71 | 0.452864 | 868.601ms | 11579 | 640 | 956278 | 8535.6 | 0.0140607 | 1(Win) | true |
| Jsonifier (two-stage) | 1223.83 | 0.3889 | 882.434ms | 11579 | 1280 | 1.57612e+06 | 9023 | 0.703125 | 2(Loss) | true |
| simdjson (reflection) | 1192.29 | 0.302128 | 935.039ms | 11579 | 4890 | 3.82884e+06 | 9261.65 | 1.84353 | 3(Loss) | true |
| simdjson (ondemand) | 1075.02 | 0.692294 | 1116.56ms | 11579 | 40 | 202279 | 10272 | 0.269263 | 4(Loss) | true |
| Glaze | 1042.78 | 0.427367 | 1110.65ms | 11579 | 320 | 655406 | 10589.6 | 0.784224 | 5(Loss) | true |
