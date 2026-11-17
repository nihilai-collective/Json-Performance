
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2712.27 | 0.275742 | 182.008ms | 4669 | 2560 | 52460.1 | 1641.69 | 0.0384127 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1388.22 | 0.0952391 | 413.076ms | 4669 | 160 | 1493.08 | 3207.5 | 0.201105 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1381.13 | 0.71251 | 346.877ms | 4669 | 320 | 168854 | 3223.97 | 0.522713 | 2(Tie) | true |
| simdjson (ondemand) | 508.367 | 0.673571 | 898.641ms | 4669 | 2560 | 8.91047e+06 | 8758.85 | 2.1359 | 4(Loss) | true |
