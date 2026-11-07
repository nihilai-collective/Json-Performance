
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5934.06 | 0.288547 | 51.391ms | 2889 | 1280 | 2297.39 | 464.297 | 0.452261 | 0.393855 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5869.86 | 0.778791 | 51.8605ms | 2889 | 160 | 2137.97 | 469.375 | 0.132979 | 0.399794 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3078.4 | 0.273975 | 94.5814ms | 2889 | 80 | 481.013 | 895 | 0 | 0.780551 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 3058.58 | 0.473605 | 94.2004ms | 2889 | 4890 | 89001.2 | 900.798 | 0.0285378 | 0.785635 | 3(Tie) | true |
