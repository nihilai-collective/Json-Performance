
----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5462.53 | 0.366515 | 67.8296ms | 2889 | 160 | 546.777 | 504.375 | 0.124069 | 0.427404 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5442.3 | 0.537956 | 55.7721ms | 2889 | 80 | 593.354 | 506.25 | 0.246305 | 0.432974 | 1(Tie) | true |
| simdjson (ondemand) | 3002.9 | 0.465936 | 94.8746ms | 2889 | 80 | 1462.03 | 917.5 | 0.547945 | 0.793077 | 3(Loss) | true |
| Glaze | 2659.99 | 0.191596 | 107.112ms | 2889 | 640 | 2520.52 | 1035.78 | 0.0150875 | 0.902167 | 4(Loss) | true |
