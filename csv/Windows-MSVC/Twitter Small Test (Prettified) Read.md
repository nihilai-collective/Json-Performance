
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1600.26 | 0.234413 | 234.45ms | 3808 | 160 | 4527.91 | 2269.38 | 0.0825537 | 1.52828 | 1(Win) | true |
| Jsonifier (two-stage) | 1433.93 | 0.251903 | 257.057ms | 3808 | 4890 | 199028 | 2532.62 | 0.564376 | 1.70609 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1366.58 | 0.409859 | 272.377ms | 3808 | 1280 | 151845 | 2657.42 | 0.825121 | 1.79038 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1354.23 | 0.225581 | 274.792ms | 3808 | 4890 | 178946 | 2681.66 | 0.199091 | 1.80762 | 3(Tie) | true |
