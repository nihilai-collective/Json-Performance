
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1246.13 | 0.305274 | 169.515ms | 2158 | 4890 | 124298 | 1651.53 | 0.327069 | 1.95365 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1237.91 | 0.466296 | 193.635ms | 2158 | 40 | 2403.85 | 1662.5 | 0.0501002 | 1.96023 | 1(Tie) | true |
| Jsonifier (two-stage) | 1217.77 | 0.190615 | 174.775ms | 2158 | 160 | 1660.38 | 1690 | 0.148148 | 1.99844 | 3(Loss) | true |
| simdjson (ondemand) | 781.036 | 0.143553 | 270.159ms | 2158 | 160 | 2289.31 | 2635 | 0.0947867 | 3.13927 | 4(Loss) | true |
