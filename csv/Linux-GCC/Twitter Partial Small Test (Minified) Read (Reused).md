
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7295.19 | 0.0901192 | 40.8967ms | 2889 | 320 | 37.0686 | 377.669 | 0.0264852 | 0.316258 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 7145.14 | 0.230241 | 41.5535ms | 2889 | 40 | 31.5282 | 385.6 | 0.00864528 | 0.323269 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 7125.73 | 0.128688 | 41.6404ms | 2889 | 160 | 39.6126 | 386.65 | 0.0161619 | 0.322659 | 2(Tie) | true |
| simdjson (reflection) | 6732.18 | 0.0747083 | 44.3812ms | 2889 | 320 | 29.9138 | 409.253 | 0.290239 | 0.343393 | 4(Loss) | true |
| Glaze | 3021.35 | 0.130924 | 95.2396ms | 2889 | 40 | 57.0154 | 911.9 | 0.021937 | 0.794843 | 5(Loss) | true |
