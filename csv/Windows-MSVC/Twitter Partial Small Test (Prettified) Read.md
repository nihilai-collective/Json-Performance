
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 6748.6 | 0.715782 | 70.8171ms | 3808 | 160 | 2373.82 | 538.125 | 0.34965 | 0.347417 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6698.04 | 0.360332 | 59.1275ms | 3808 | 640 | 2442.78 | 542.188 | 0 | 0.350755 | 1(Tie) | true |
| simdjson (ondemand) | 3865.97 | 0.291207 | 98.6766ms | 3808 | 320 | 2394.59 | 939.375 | 0.0664894 | 0.620009 | 3(Loss) | true |
| Glaze | 3286.51 | 0.315829 | 115.596ms | 3808 | 40 | 487.179 | 1105 | 0.151057 | 0.735347 | 4(Loss) | true |
