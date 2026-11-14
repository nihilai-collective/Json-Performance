
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2099.61 | 0.0674342 | 3026.74ms | 56369 | 2560 | 763137 | 25603.6 | 0.0445296 | 1.44617 | 1(Win) | true |
| Glaze | 1886.17 | 0.0874471 | 3297.47ms | 56369 | 2560 | 1.59019e+06 | 28500.9 | 0.101113 | 1.60979 | 2(Loss) | true |
| Jsonifier (two-stage) | 1546.2 | 0.108094 | 3965.25ms | 56369 | 160 | 225981 | 34767.5 | 0.25592 | 1.96419 | 3(Loss) | true |
| simdjson (ondemand) | 998.69 | 0.0810189 | 5797.07ms | 56369 | 1280 | 2.43446e+06 | 53828.2 | 0.00914284 | 3.04198 | 4(Loss) | true |
