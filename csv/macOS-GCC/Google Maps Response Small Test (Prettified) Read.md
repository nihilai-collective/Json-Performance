
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2287.82 | 0.295103 | 394.039ms | 9378 | 1280 | 170346 | 3909.2 | 0.0409458 | 1(Win) | true |
| Jsonifier (two-stage) | 2176.05 | 0.274785 | 415.178ms | 9378 | 1280 | 163260 | 4110 | 0.0194609 | 2(Loss) | true |
| simdjson (reflection) | 1966.14 | 0.993273 | 464.799ms | 9378 | 160 | 326626 | 4548.8 | 0.0351617 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1465.24 | 0.174853 | 649.482ms | 9378 | 1280 | 145800 | 6103.8 | 0.212529 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1458.7 | 0.305739 | 601.797ms | 9378 | 2560 | 899567 | 6131.2 | 0.182339 | 4(Tie) | true |
