
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4226.24 | 0.200222 | 8381.23ms | 716365 | 320 | 3.35225e+07 | 161652 | 0.223586 | 0.58547 | 1(Win) | true |
| Glaze | 2793.79 | 0.111391 | 6274.51ms | 716365 | 1280 | 9.49715e+07 | 244535 | 0.0591015 | 0.885759 | 2(Loss) | true |
