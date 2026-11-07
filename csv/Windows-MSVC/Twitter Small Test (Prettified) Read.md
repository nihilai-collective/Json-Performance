
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1762.91 | 0.281153 | 211.038ms | 3808 | 80 | 2683.54 | 2060 | 0 | 1.38045 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1447.57 | 0.119372 | 268.992ms | 3808 | 320 | 2869.91 | 2508.75 | 0.35 | 1.68991 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1438.34 | 0.313621 | 256.757ms | 3808 | 1280 | 80258 | 2524.84 | 0.0123755 | 1.70242 | 2(Tie) | true |
| Jsonifier | 1393.31 | 0.275719 | 264.784ms | 3808 | 4890 | 252544 | 2606.44 | 0.110918 | 1.75804 | 4(Loss) | true |
