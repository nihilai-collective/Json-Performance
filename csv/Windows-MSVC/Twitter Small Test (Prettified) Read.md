
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1800.21 | 0.440061 | 215.941ms | 3808 | 4890 | 385376 | 2017.32 | 0.467714 | 1.6718 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1798.65 | 0.303522 | 221.717ms | 3808 | 320 | 12017.9 | 2019.06 | 1.44905 | 1.67208 | 1(Tie) | true |
| simdjson (ondemand) | 1694.37 | 0.429325 | 221.737ms | 3808 | 30 | 2540.23 | 2143.33 | 0.312012 | 1.77485 | 3(Loss) | true |
| Jsonifier | 1552.79 | 0.234364 | 234.69ms | 3808 | 80 | 2403.48 | 2338.75 | 0.160085 | 1.93919 | 4(Loss) | true |
