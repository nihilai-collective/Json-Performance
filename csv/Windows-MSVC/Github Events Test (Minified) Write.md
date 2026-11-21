
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11671.4 | 0.19354 | 508.143ms | 58581 | 30 | 2574.71 | 4786.67 | 0.139082 | 0.211245 | 1(Win) | true |
| Glaze | 4746.92 | 0.179958 | 1187.42ms | 58581 | 2560 | 1.14835e+06 | 11769.1 | 0.145826 | 0.520067 | 2(Loss) | true |
