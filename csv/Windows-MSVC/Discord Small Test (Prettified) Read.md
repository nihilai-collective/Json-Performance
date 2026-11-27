
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1385.49 | 0.222122 | 489.703ms | 6701 | 40 | 4198.72 | 4612.5 | 0.234319 | 1.77899 | 1(Win) | true |
| Jsonifier (two-stage) | 1196.04 | 0.337609 | 546.086ms | 6701 | 1280 | 416513 | 5343.12 | 0.05261 | 2.05816 | 2(Loss) | true |
| Glaze | 1028.97 | 0.43058 | 648.687ms | 6701 | 1280 | 915352 | 6210.62 | 0.0301993 | 2.39373 | 3(Loss) | true |
| simdjson (ondemand) | 878.052 | 0.09721 | 754.925ms | 6701 | 160 | 8009.04 | 7278.12 | 0.0772267 | 2.80891 | 4(Loss) | true |
