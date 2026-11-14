
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2673.43 | 2.82091 | 159.434ms | 3808 | 160 | 234938 | 1358.4 | 1.31265 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2469.29 | 0.716718 | 169.816ms | 3808 | 2560 | 284436 | 1470.7 | 0.526316 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2435.51 | 0.73057 | 168.536ms | 3808 | 2560 | 303792 | 1491.1 | 0.981986 | 2(Tie) | true |
| simdjson (reflection) | 1820.35 | 0.438318 | 216.291ms | 3808 | 1280 | 97875.5 | 1995 | 0.574713 | 4(Loss) | true |
| simdjson (ondemand) | 1484.52 | 0.433006 | 266.028ms | 3808 | 2560 | 287242 | 2446.3 | 0.208044 | 5(Loss) | true |
