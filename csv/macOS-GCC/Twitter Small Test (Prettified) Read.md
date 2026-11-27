
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2517.92 | 0.720879 | 147.086ms | 3808 | 2560 | 276743 | 1442.3 | 0.312978 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2195.85 | 0.469826 | 167.815ms | 3808 | 4890 | 295238 | 1653.84 | 0.500958 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2184.99 | 0.433692 | 168.386ms | 3808 | 4890 | 254077 | 1662.06 | 0.232963 | 2(Tie) | true |
| simdjson (reflection) | 1744.78 | 0.215198 | 211.43ms | 3808 | 4890 | 98106.4 | 2081.4 | 0.0815895 | 4(Loss) | true |
| simdjson (ondemand) | 1381.88 | 0.751331 | 258.829ms | 3808 | 640 | 249513 | 2628 | 0 | 5(Loss) | true |
